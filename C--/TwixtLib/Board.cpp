#include "Board.h"

IBoardPtr IBoard::CreateBoard()
{
	return std::make_shared<Board>();
}

Board::Board()
	: m_boardSize{ 24 }
	, m_turn{ EPiece::RedPeg }
{
	InitializeBridgeGenerators();
	InitializeBoard(m_boardSize);
}

Board::Board(int boardSize)
	: m_boardSize{ boardSize }
{
	for (int row = 0; row < m_boardSize; row++)
		for (int col = 0; col < m_boardSize; col++)
			m_board[row][col] = EPiece::None;
}

EPiece Board::GetPiece(int line, int column) const
{
	return m_board[line][column];
}

std::unordered_set<Bridge> Board::GetBridges() const
{
	return m_bridges;
}

void Board::PlacePeg(int line, int column)
{
	//to do
}

void Board::PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	//TO DO
}

void Board::RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	//TO DO
}

bool Board::CheckGameWon(int line, int column)
{
	//TO DO
}

void Board::SwitchTurn()
{
	m_turn = (m_turn == EPiece::RedPeg) ? EPiece::BlackPeg : EPiece::RedPeg;
}

void Board::InitializeBoard(int boardSize)
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
	m_vBridgeGenerator3.emplace_back(Position(0, -2), Position(2, 1));
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
