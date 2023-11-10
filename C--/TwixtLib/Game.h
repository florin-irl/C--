#pragma once
#include "EGameState.h";
#include "EPiece.h";
#include "IBoard.h";
#include "IGame.h"

class Game : public IGame
{
public:
	Game();
	Game(int boardSize, int nrPegs, int nrBridges);

	EGameState GetGameState() const;
	std::unordered_set<Bridge> GetBridges();

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

