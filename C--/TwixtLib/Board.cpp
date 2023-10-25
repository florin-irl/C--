#include "Board.h"

Board::Board()
	:m_boardSize{ 24 }
	, m_turn{ Peg::RedPeg }
	, m_nrOfPegsPlayer1{ 50 }
	, m_nrOfBridgesPlayer1{ 50 }
	, m_nrOfPegsPlayer2{ 50 }
	, m_nrOfBridgesPlayer2{ 50 }
{
	m_board.resize(m_boardSize);
	for (int row = 0; row < m_boardSize; row++)
	{
		m_board[row].resize(m_boardSize);
		for (int column = 0; column < m_boardSize; column++)
			m_board[row][column] = nullptr;
	}

}

Board::Board(int boardSize, int nrPegs, int nrBridges)
	:m_boardSize{ boardSize }
	, m_turn{ Peg::RedPeg }
	, m_nrOfPegsPlayer1{ nrPegs }
	, m_nrOfBridgesPlayer1{ nrBridges }
	, m_nrOfPegsPlayer2{ nrPegs }
	, m_nrOfBridgesPlayer2{ nrBridges }
{
	m_board.resize(m_boardSize);

	for (int row = 0; row < m_boardSize; row++)
	{
		m_board[row].resize(m_boardSize);
		for (int column = 0; column < m_boardSize; column++)
			m_board[row][column] = nullptr;
	}
}

void Board::switchTurn()
{
	if (m_turn == Peg::RedPeg)
		m_turn = Peg::BlackPeg;
	else
		m_turn = Peg::RedPeg;
}

