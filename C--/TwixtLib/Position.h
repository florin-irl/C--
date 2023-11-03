#pragma once
class Position
{
public:
	Position(int row,int col);

	int GetRow() const;

private:
	int m_row;
	int m_col;
};

