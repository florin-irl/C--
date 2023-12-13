#pragma once
#include "EGameState.h"
#include "IBoard.h"
#include <string>

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr CreateGame();

	virtual EPiece GetTurn() const = 0;
	virtual EGameState GetGameState() const = 0;
	virtual EPiece GetPiece(int line, int column) const = 0;
	virtual std::unordered_set<Bridge> GetBridges() const = 0;

	virtual int GetNrRedPegsRemaining() const = 0;
	virtual int GetNrRedBridgesRemaining() const = 0;

	virtual int GetNrBlackPegsRemaining() const = 0;
	virtual int GetNrBlackBridgesRemaining() const = 0;

	virtual void PlacePeg(int line, int column) = 0; // Can throw exceptions //
	virtual void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0; // Can throw exceptions //
	virtual void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0; // Can throw exceptions //

	virtual bool IsGameOver() const = 0;
	virtual void SwitchTurn() = 0; // Can throw exceptions //

	virtual void SaveGame(const std::string& fileName) const = 0;
	virtual void LoadGame(const std::string& fileName) = 0;
	virtual void RestartGame() = 0;

	virtual ~IGame() = default;

};