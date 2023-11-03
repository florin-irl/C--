#include "Board.h"

Board::Board()
	:m_boardSize{24}
{
	for (int row = 0;row < m_boardSize;row++)
		for (int col = 0;col < m_boardSize;col++)
			m_board[row][col] = EPiece::None;
}
