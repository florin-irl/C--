#include "Board.h"
#include "GameExceptions.h"

// Utility functions //

void Swap(int& x, int& y)
{
	int aux = x;
	x = y;
	y = aux;
}

// Board Functions //

IBoardPtr IBoard::CreateBoard()
{
	return std::make_shared<Board>();
}

Board::Board()
	: m_boardSize{ 24 }
	, m_turn{ EPiece::RedPeg }
{
	InitializeBridgeGenerators();
	ResizeBoard(m_boardSize);
	InitializeBoard();
}

Board::Board(int boardSize)
	:m_boardSize{ boardSize }
	, m_turn{ EPiece::RedPeg }
{
	InitializeBridgeGenerators();
	ResizeBoard(m_boardSize);
	InitializeBoard();
}

int Board::GetBoardSize() const
{
	return m_boardSize;
}

EPiece Board::GetTurn() const
{
	return m_turn;
}

EPiece Board::GetPiece(int line, int column) const
{
	if (line < 0 || line > m_boardSize - 1 || column < 0 || column > m_boardSize - 1)
		throw OutOfBoundsException("Line or column is out of bounds !");
	return m_board[line][column];
}

std::vector<std::vector<EPiece>> Board::GetBoard() const
{
	return m_board;
}

std::unordered_set<Bridge> Board::GetBridges() const
{
	return m_bridges;
}

void Board::PlacePeg(int line, int column)
{
	// Poti adauga o exceptie care este aruncata atunci cand incerci sa pui un peg de 2 in aceasi tura //

	if (line < 0 || line > m_boardSize - 1 || column < 0 || column > m_boardSize - 1)
		throw OutOfBoundsException("Line or column is out of bounds !");

	if (
		(m_turn == EPiece::RedPeg && (column == 0 || column == m_boardSize - 1))
		||
		(m_turn == EPiece::BlackPeg && (line == 0 || line == m_boardSize - 1))
		)
		throw EnemyBaseException("You can't place pegs in enemy base !");

	if (m_board[line][column] != EPiece::None)
		throw OcuppiedPositionException("This position is already occupied !");

	m_board[line][column] = m_turn;
}

void Board::PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	// Verifica ca Bridge-ul sa fie de sus in jos //
	if (firstLine > secondLine)
	{
		Swap(firstLine, secondLine);
		Swap(firstColumn, secondColumn);
	}

	// Arunca exceptiile necesare //

	if (firstLine < 0 || firstLine > m_boardSize - 1 || firstColumn < 0 || firstColumn > m_boardSize - 1)
		throw OutOfBoundsException("Line or column is out of bounds !");

	if (secondLine < 0 || secondLine > m_boardSize - 1 || secondColumn < 0 || secondColumn > m_boardSize - 1)
		throw OutOfBoundsException("Line or column is out of bounds !");

	if (m_board[firstLine][firstColumn] != m_turn || m_board[secondLine][secondColumn] != m_turn)
		throw InvalidPegsForBridgeException("You can't make a bridge with a piece that is not yours !");

	if (firstLine + 2 != secondLine && firstLine + 1 != secondLine)
		throw CantFormBridgeException("The positions you provided don't form a bridge !");

	if (firstLine + 2 == secondLine)
	{
		if (firstColumn - 1 != secondColumn && firstColumn + 1 != secondColumn)
			throw CantFormBridgeException("The positions you provided don't form a bridge !");
	}
	if (firstLine + 1 == secondLine)
	{
		if (firstColumn - 2 != secondColumn && firstColumn + 2 != secondColumn)
			throw CantFormBridgeException("The positions you provided don't form a bridge !");
	}

	std::vector<Bridge> vBridgeGenerator;

	if (firstLine + 2 == secondLine && firstColumn + 1 == secondColumn)
		vBridgeGenerator = m_vBridgeGenerator1;

	if (firstLine + 2 == secondLine && firstColumn - 1 == secondColumn)
		vBridgeGenerator = m_vBridgeGenerator2;

	if (firstLine + 1 == secondLine && firstColumn - 2 == secondColumn)
		vBridgeGenerator = m_vBridgeGenerator3;

	if (firstLine + 1 == secondLine && firstColumn + 2 == secondColumn)
		vBridgeGenerator = m_vBridgeGenerator4;

	for (const auto& bridge : vBridgeGenerator)
	{
		Bridge bridgeToVerify = Bridge(
			Position(firstLine + bridge.GetFirstPegPos().GetRow(), firstColumn + bridge.GetFirstPegPos().GetCol()),
			Position(firstLine + bridge.GetSecondPegPos().GetRow(), firstColumn + bridge.GetSecondPegPos().GetCol())
		);
		if (m_bridges.find(bridgeToVerify) != m_bridges.end())
			throw BridgeInTheWayException("Another bridge is blocking the bridge you want to place !");
	}	

	m_bridges.emplace(Position(firstLine, firstColumn), Position(secondLine, secondColumn));
}

void Board::RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	// Verifica ca Bridge-ul sa fie de sus in jos //
	if (firstLine > secondLine)
	{
		Swap(firstLine, secondLine);
		Swap(firstColumn, secondColumn);
	}

	if (m_board[firstLine][firstColumn] != m_turn || m_board[secondLine][secondColumn] != m_turn)
		throw InvalidPegsForBridgeException("You can't remove a bridge that is not yours !");

	Bridge bridge(Position(firstLine, firstColumn), Position(secondLine, secondColumn));
	if (m_bridges.find(bridge) == m_bridges.end())
		throw InexistentBridgeException("The bridge you want to remove doesn't exist !");

	Bridge bridgeToErase(Position(firstLine, firstColumn), Position(secondLine, secondColumn));
	m_bridges.erase(bridgeToErase);
}

bool Board::CheckGameWon(int line, int column)
{
	// TO DOO //
	return false;
}

void Board::SwitchTurn()
{
	m_turn = (m_turn == EPiece::RedPeg) ? EPiece::BlackPeg : EPiece::RedPeg;
}

void Board::LoadBoard(const std::ostringstream& stringBoard)
{
	std::string result = stringBoard.str();
	std::istringstream inputStream(result);

	// Read Turn // 
	int turn;
	inputStream >> turn;
	m_turn = static_cast<EPiece>(turn);

	// Read Board Size //
	inputStream >> m_boardSize;
	ResizeBoard(m_boardSize);

	// Read Board //
	int piece;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			inputStream >> piece;
			m_board[i][j] = static_cast<EPiece>(piece);
		}
	}

	// Read Bridges //
	m_bridges.clear();
	int firstRow, firstCol, secondRow, secondCol;
	while (inputStream >> firstRow >> firstCol >> secondRow >> secondCol) {
		m_bridges.emplace(Position(firstRow, firstCol), Position(secondRow, secondCol));
	}
}

void Board::ResetBoard()
{
	// Reset Turn //
	m_turn = EPiece::RedPeg;

	// Reset Board //
	InitializeBoard();

	// Reset Bridges //
	m_bridges.clear();
}

// Private Methods //

void Board::ResizeBoard(int boardSize)
{
	m_board.resize(boardSize);
	for (int i = 0; i < boardSize; i++)
		m_board[i].resize(boardSize);
}

void Board::InitializeBoard()
{
	for (int row = 0; row < m_boardSize; row++)
		for (int col = 0; col < m_boardSize; col++)
			m_board[row][col] = EPiece::None;
}

void Board::InitializeBridgeGenerators()
{
	InitializeBridgeGenerator1();
	InitializeBridgeGenerator2();
	InitializeBridgeGenerator3();
	InitializeBridgeGenerator4();
}

void Board::InitializeBridgeGenerator1()
{
	m_vBridgeGenerator1.emplace_back(Position(0, 1), Position(1, -1));
	m_vBridgeGenerator1.emplace_back(Position(0, 2), Position(1, 0));
	m_vBridgeGenerator1.emplace_back(Position(1, 1), Position(2, -1));
	m_vBridgeGenerator1.emplace_back(Position(1, 2), Position(2, 0));
	m_vBridgeGenerator1.emplace_back(Position(0, -1), Position(1, 1));
	m_vBridgeGenerator1.emplace_back(Position(1, 0), Position(2, 2));
	m_vBridgeGenerator1.emplace_back(Position(-1, 1), Position(1, 0));
	m_vBridgeGenerator1.emplace_back(Position(0, 1), Position(2, 0));
	m_vBridgeGenerator1.emplace_back(Position(1, 1), Position(3, 0));
}

void Board::InitializeBridgeGenerator2()
{
	m_vBridgeGenerator2.emplace_back(Position(0, -1), Position(1, 1));
	m_vBridgeGenerator2.emplace_back(Position(0, -2), Position(1, 0));
	m_vBridgeGenerator2.emplace_back(Position(1, -1), Position(2, 1));
	m_vBridgeGenerator2.emplace_back(Position(1, -2), Position(2, 0));
	m_vBridgeGenerator2.emplace_back(Position(-1, -1), Position(1, 0));
	m_vBridgeGenerator2.emplace_back(Position(0, -1), Position(2, 0));
	m_vBridgeGenerator2.emplace_back(Position(0, 1), Position(1, -1));
	m_vBridgeGenerator2.emplace_back(Position(1, 0), Position(2, -2));
	m_vBridgeGenerator2.emplace_back(Position(1, -1), Position(3, 0));
}

void Board::InitializeBridgeGenerator3()
{
	m_vBridgeGenerator3.emplace_back(Position(0, -3), Position(1, -1));
	m_vBridgeGenerator3.emplace_back(Position(0, -2), Position(1, 0));
	m_vBridgeGenerator3.emplace_back(Position(0, -1), Position(1, 1));
	m_vBridgeGenerator3.emplace_back(Position(0, -2), Position(2, -1));
	m_vBridgeGenerator3.emplace_back(Position(0, -1), Position(2, 0));
	m_vBridgeGenerator3.emplace_back(Position(-1, -1), Position(1, 0));
	m_vBridgeGenerator3.emplace_back(Position(-1, -2), Position(1, -1));
	m_vBridgeGenerator3.emplace_back(Position(0, -1), Position(2, -2));
	m_vBridgeGenerator3.emplace_back(Position(-1, 0), Position(1, -1));
}

void Board::InitializeBridgeGenerator4()
{
	m_vBridgeGenerator4.emplace_back(Position(-1, 1), Position(1, 0));
	m_vBridgeGenerator4.emplace_back(Position(0, 1), Position(2, 0));
	m_vBridgeGenerator4.emplace_back(Position(-1, 2), Position(1, 1));
	m_vBridgeGenerator4.emplace_back(Position(0, 2), Position(2, 1));
	m_vBridgeGenerator4.emplace_back(Position(0, 1), Position(2, 2));
	m_vBridgeGenerator4.emplace_back(Position(-1, 0), Position(1, 1));
	m_vBridgeGenerator4.emplace_back(Position(0, 1), Position(1, -1));
	m_vBridgeGenerator4.emplace_back(Position(0, 2), Position(1, 0));
	m_vBridgeGenerator4.emplace_back(Position(0, 3), Position(1, 1));
}