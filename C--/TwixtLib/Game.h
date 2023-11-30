#pragma once
#include "IGame.h"

class Game : public IGame
{
public:
	Game();
	Game(int boardSize, int nrPegs, int nrBridges);

	EPiece GetTurn() const override;
	EGameState GetGameState() const;
	EPiece GetPiece(int line, int column);
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

