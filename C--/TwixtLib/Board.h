#pragma once
#include "Peg.h"
#include <vector>
class Board
{
public:
	Board();
	Board(int boardSize, int nrPegs, int nrBridges);
	~Board() = default;

	void switchTurn();
private:
	int m_boardSize;
	Peg m_turn;

	int m_nrOfPegsPlayer1;
	int m_nrOfBridgesPlayer1;
	int m_nrOfPegsPlayer2;
	int m_nrOfBridgesPlayer2;


	std::vector<std::vector<Peg*>> m_board;
};

