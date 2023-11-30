#pragma once
#include "EGameState.h"
#include "IBoard.h"
#include <unordered_set>  // sterge daca da erori pt ca e si in iboard //
#include <memory> // sterge daca da erori pt ca e si in iboard //

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr CreateGame();
	virtual EPiece GetTurn() const = 0;
	virtual EGameState GetGameState() = 0;
	virtual EPiece GetPiece(int line, int column) = 0;
	virtual std::unordered_set<Bridge> GetBridges() = 0;
	virtual void PlacePeg(int line, int column) = 0; // Can throw exceptions //
	virtual void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0;
	virtual void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0;
	virtual bool IsGameOver() = 0;
	virtual void SwitchTurn() = 0; // Can throw exceptions //
	virtual ~IGame() = default;
};