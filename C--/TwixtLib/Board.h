#pragma once
#include "Peg.h"
#include <vector>
class Board
{
public:
	Board();
	Board(int boardSize, int nrPegs, int nrBridges);
	~Board() = default;

	void PlacePeg(int line, int column);
	Peg GetTurn() const;
	void SwitchTurn();
private:
	int m_boardSize;
	Peg m_turn;

	int m_redPegsRemaining;
	int m_redBridgesRemaining;
	int m_blackPegsRemaining;
	int m_blackBridgesRemaining;

	std::vector<std::vector<Peg*>> m_board;
};

