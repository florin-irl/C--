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
};