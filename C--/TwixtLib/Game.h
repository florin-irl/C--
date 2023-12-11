#pragma once
#include "IGame.h"

class Game : public IGame
{
public:
	Game();
	Game(int boardSize, int nrPegs, int nrBridges);

	EPiece GetTurn() const override;
	EGameState GetGameState() const override;
	EPiece GetPiece(int line, int column) const override;
	std::unordered_set<Bridge> GetBridges() const override;
	void PlacePeg(int line, int column) override;
	void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;  // Verifici daca jocul s a terminat de fiecare data cand plasezi un bridge
	void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;
	bool IsGameOver() const override;
	void SwitchTurn() override;
	//Verifica pe viitor sa ai voie sa aplici PlacePeg o singura data pe tura //
	//Fa o functie de reset Game //

	void SaveGame(std::ofstream& out) const override;

private:
	int m_boardSize;
	EGameState m_gameState;
	IBoardPtr m_board;
	int m_redPegsRemaining;
	int m_redBridgesRemaining;
	int m_blackPegsRemaining;
	int m_blackBridgesRemaining;

	void ChangeStateIfDraw();
	void ChangeStateIfGameWon(int line, int column);
};

