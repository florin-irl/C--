#pragma once
#include "EGameState.h";
#include "EPiece.h";
#include "IBoard.h";

class Game
{
public:
	Game();
	Game(int boardSize, int nrPegs, int nrBridges);
private:
	EGameState m_gameState;
	EPiece m_turn;
	int m_boardSize;
	IBoard* m_board;
	int m_redPegsRemaining;
	int m_redBridgesRemaining;
	int m_blackPegsRemaining;
	int m_blackBridgesRemaining;
};

