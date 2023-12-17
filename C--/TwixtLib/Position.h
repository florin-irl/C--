#pragma once
class Position
{
public:
	Position();
	Position(int row, int col);

	int GetRow() const;
	int GetCol() const;

	bool operator==(const Position& other) const;

private:
	int m_row;
	int m_col;
};

