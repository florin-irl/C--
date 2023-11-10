#pragma once
#include "EGameState.h"
#include "EPiece.h"
#include "Bridge.h"
#include <unordered_set>

class IGame
{
public:
	virtual EGameState GetGameState() = 0;
	virtual EPiece GetPiece(int line, int column) = 0;
	virtual std::unordered_set<Bridge> GetBridges() = 0;
	virtual void PlacePeg(int line, int column) = 0;
	virtual void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0;
	virtual void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0;
	virtual bool IsGameOver() = 0;
	virtual void SwitchTurn() = 0;
};