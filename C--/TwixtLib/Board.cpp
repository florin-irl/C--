#include "Board.h"

Board::Board()
	:m_boardSize{ 24 }
	, m_turn{ Peg::RedPeg }
	, m_redPegsRemaining{ 50 }
	, m_redBridgesRemaining{ 50 }
	, m_blackPegsRemaining{ 50 }
	, m_blackBridgesRemaining{ 50 }
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
	, m_redPegsRemaining{ nrPegs }
	, m_redBridgesRemaining{ nrBridges }
	, m_blackPegsRemaining{ nrPegs }
	, m_blackBridgesRemaining{ nrBridges }
{
	m_board.resize(m_boardSize);

	for (int row = 0; row < m_boardSize; row++)
	{
		m_board[row].resize(m_boardSize);
		for (int column = 0; column < m_boardSize; column++)
			m_board[row][column] = nullptr;
	}
}

void Board::PlacePeg(int line, int column)
{
	if (line<0 || line>m_boardSize - 1)
	{
		//throw exception
	}

	if (column<0 || column>m_boardSize - 1)
	{
		//throw exception
	}

	if (m_board[line][column])
	{
		//throw exception
	}


	if (
		(line == 0 && column == 0)
		|| (line == 0 && column == m_boardSize - 1)
		|| (line == m_boardSize - 1 && column == 0)
		|| (line == m_boardSize - 1 && column == m_boardSize - 1)
		)
	{
		//throw exception
	}

	if (m_turn == Peg::RedPeg && (column == 0 || column == m_boardSize - 1))
	{
		//throw exception
	}

	if (m_turn == Peg::BlackPeg && (line == 0 || line == m_boardSize - 1))
	{
		//throw exception
	}

	m_board[line][column] = new Peg(m_turn);
	
	if (m_turn == Peg::RedPeg)
		m_redPegsRemaining--;
	else
		m_blackPegsRemaining--;
}

void Board::SwitchTurn()
{
	m_turn = (m_turn == Peg::RedPeg) ? Peg::BlackPeg : Peg::RedPeg;
}

Peg Board::GetTurn() const
{
	return m_turn;
}