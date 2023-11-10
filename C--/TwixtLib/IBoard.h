#pragma once

#include "EPiece.h"
#include "Bridge.h"
#include <unordered_set>

class IBoard
{
public:
	virtual EPiece GetPiece(int line, int column) const = 0;
	virtual std::unordered_set<Bridge> GetBridges() const = 0;
	
};

