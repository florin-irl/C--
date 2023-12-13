#pragma once
#include "EGameState.h"
#include "IBoard.h"
#include <fstream>
#include <unordered_set>  // sterge daca da erori pt ca e si in iboard //
#include <memory> // sterge daca da erori pt ca e si in iboard //

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

	virtual ~IGame() = default;

	virtual void SaveGame(std::ofstream& out) const = 0;
	virtual void LoadGame(std::istream& in) = 0;
	virtual void RestartGame() = 0;

};