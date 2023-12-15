#pragma once
#include "IGame.h"

class Game : public IGame
{
public:
	Game();
	Game(int boardSize, int nrPegs, int nrBridges);

	int GetBoardSize() const;

	EPiece GetTurn() const override;
	EGameState GetGameState() const override;

	EPiece GetPiece(int line, int column) const override;
	std::unordered_set<Bridge> GetBridges() const override;

	int GetNrRedPegsRemaining() const;
	int GetNrRedBridgesRemaining() const;

	int GetNrBlackPegsRemaining() const;
	int GetNrBlackBridgesRemaining() const;

	void PlacePeg(int line, int column) override;
	void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;  // Verifici daca jocul s a terminat de fiecare data cand plasezi un bridge
	void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;

	bool IsGameOver() const override;
	void SwitchTurn() override;

	void SaveGame(const std::string& fileName) const override;
	void LoadGame(const std::string& fileName) override;
	void RestartGame() override;

	void SetUpGame(int boardSize, int nrPegs, int nrBridges) override;

private:
	EGameState m_gameState;
	IBoardPtr m_board;

	int m_nrPegs;
	int m_nrBridges;

	int m_redPegsRemaining;
	int m_redBridgesRemaining;
	int m_blackPegsRemaining;
	int m_blackBridgesRemaining;

	bool m_pegPlaced;

	void ChangeStateIfDraw();
	void ChangeStateIfGameWon(int line, int column);
};

