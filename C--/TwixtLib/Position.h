#pragma once
class Position
{
public:
	Position(int row,int col);

	int GetRow() const;
	int GetCol() const;

	bool operator==(const Position& other);

private:
	int m_row;
	int m_col;
};

