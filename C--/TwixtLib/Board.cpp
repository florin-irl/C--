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