#include "Board.h"
#include "GameExceptions.h"
#include <queue>

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

void Board::SetBoardSize(int boardSize)
{
	m_boardSize = boardSize;
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

	std::array<Bridge,9> vBridgeGenerator;

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
	std::vector<std::vector<bool>> visitedMatrix(m_boardSize, std::vector<bool>(m_boardSize, false));
	visitedMatrix[line][column] = true;

	std::queue<Position> unvisitedPegQ;

	bool conectedBase1 = false;
	bool conectedBase2 = false;

	if (line == 0 || column == 0)
		conectedBase1 = true;

	if (line == m_boardSize - 1 || column == m_boardSize - 1)
		conectedBase2 = true;

	unvisitedPegQ.push(Position(line, column));
	while (!unvisitedPegQ.empty())
	{
		Position currentPeg = unvisitedPegQ.front();
		unvisitedPegQ.pop();

		std::list<Position> validPegs = GetValidPegs(currentPeg.GetRow(), currentPeg.GetCol());
		for (const auto& peg : validPegs)
		{
			if (!visitedMatrix[peg.GetRow()][peg.GetCol()])
			{
				visitedMatrix[peg.GetRow()][peg.GetCol()] = true;
				unvisitedPegQ.push(peg);

				if (peg.GetRow() == 0 || peg.GetCol() == 0)
					conectedBase1 = true;

				if (peg.GetRow() == m_boardSize - 1 || peg.GetCol() == m_boardSize - 1)
					conectedBase2 = true;

				if (conectedBase1 && conectedBase2)
					return true;
			}
		}
	}
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

	// Resize Board //
	ResizeBoard(m_boardSize);

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
	m_vBridgeGenerator1[0] = Bridge(Position( 0,  1), Position(1, -1));
	m_vBridgeGenerator1[1] = Bridge(Position( 0,  2), Position(1,  0));
	m_vBridgeGenerator1[2] = Bridge(Position( 1,  1), Position(2, -1));
	m_vBridgeGenerator1[3] = Bridge(Position( 1,  2), Position(2,  0));
	m_vBridgeGenerator1[4] = Bridge(Position( 0, -1), Position(1,  1));
	m_vBridgeGenerator1[5] = Bridge(Position( 1,  0), Position(2,  2));
	m_vBridgeGenerator1[6] = Bridge(Position(-1,  1), Position(1,  0));
	m_vBridgeGenerator1[7] = Bridge(Position( 0,  1), Position(2,  0));
	m_vBridgeGenerator1[8] = Bridge(Position( 1,  1), Position(3,  0));
}

void Board::InitializeBridgeGenerator2()
{
	m_vBridgeGenerator2[0] = Bridge(Position( 0, -1), Position(1,  1));
	m_vBridgeGenerator2[1] = Bridge(Position( 0, -2), Position(1,  0));
	m_vBridgeGenerator2[2] = Bridge(Position( 1, -1), Position(2,  1));
	m_vBridgeGenerator2[3] = Bridge(Position( 1, -2), Position(2,  0));
	m_vBridgeGenerator2[4] = Bridge(Position(-1, -1), Position(1,  0));
	m_vBridgeGenerator2[5] = Bridge(Position( 0, -1), Position(2,  0));
	m_vBridgeGenerator2[6] = Bridge(Position( 0,  1), Position(1, -1));
	m_vBridgeGenerator2[7] = Bridge(Position( 1,  0), Position(2, -2));
	m_vBridgeGenerator2[8] = Bridge(Position( 1, -1), Position(3,  0));
}

void Board::InitializeBridgeGenerator3()
{
	m_vBridgeGenerator3[0] = Bridge(Position( 0, -3), Position(1, -1));
	m_vBridgeGenerator3[1] = Bridge(Position( 0, -2), Position(1,  0));
	m_vBridgeGenerator3[2] = Bridge(Position( 0, -1), Position(1,  1));
	m_vBridgeGenerator3[3] = Bridge(Position( 0, -2), Position(2, -1));
	m_vBridgeGenerator3[4] = Bridge(Position( 0, -1), Position(2,  0));
	m_vBridgeGenerator3[5] = Bridge(Position(-1, -1), Position(1,  0));
	m_vBridgeGenerator3[6] = Bridge(Position(-1, -2), Position(1, -1));
	m_vBridgeGenerator3[7] = Bridge(Position( 0, -1), Position(2, -2));
	m_vBridgeGenerator3[8] = Bridge(Position(-1,  0), Position(1, -1));
}

void Board::InitializeBridgeGenerator4()
{
	m_vBridgeGenerator4[0] = Bridge(Position(-1, 1), Position(1,  0));
	m_vBridgeGenerator4[1] = Bridge(Position( 0, 1), Position(2,  0));
	m_vBridgeGenerator4[2] = Bridge(Position(-1, 2), Position(1,  1));
	m_vBridgeGenerator4[3] = Bridge(Position( 0, 2), Position(2,  1));
	m_vBridgeGenerator4[4] = Bridge(Position( 0, 1), Position(2,  2));
	m_vBridgeGenerator4[5] = Bridge(Position(-1, 0), Position(1,  1));
	m_vBridgeGenerator4[6] = Bridge(Position( 0, 1), Position(1, -1));
	m_vBridgeGenerator4[7] = Bridge(Position( 0, 2), Position(1,  0));
	m_vBridgeGenerator4[8] = Bridge(Position( 0, 3), Position(1,  1));
}

std::list<Position> Board::GetValidPegs(int line, int column)
{
	std::list<Position> validPegs; // The Pegs that make bridge with line and column //
	std::list<Position> PegsToVerify = { {-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1} };
	int firstLine, firstColumn, secondLine, secondColumn;

	for (const auto& peg : PegsToVerify)
	{
		firstLine = line;
		firstColumn = column;
		secondLine = line + peg.GetRow();
		secondColumn = column + peg.GetCol();

		if (firstLine > secondLine)
		{
			Swap(firstLine, secondLine);
			Swap(firstColumn, secondColumn);
		}

		Bridge possibleBridge = Bridge{ Position{firstLine,firstColumn} ,Position{secondLine,secondColumn} };
		if (m_bridges.find(possibleBridge) != m_bridges.end())
			validPegs.emplace_back(line + peg.GetRow(), column + peg.GetCol());
	}
	return validPegs;
}
