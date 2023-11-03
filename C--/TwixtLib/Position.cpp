#include "Position.h"

Position::Position(int row, int col)
	:m_row{row}
	,m_col{col}
{
}

int Position::GetRow() const
{
	return m_row;
}

