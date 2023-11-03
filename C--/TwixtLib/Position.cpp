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

int Position::GetCol() const
{
	return m_col;
}

bool Position::operator==(const Position& other)
{
	if (this->GetCol() != other.m_col)return false;
	if (this->GetRow() != other.m_row)return false;
	return true;
}

