#pragma once
#include "EPiece.h"
#include "Bridge.h"
#include <vector>
#include <unordered_set>

class Board
{
public:
	Board();
	Board(int boardSize);
private:
	int m_boardSize;
	std::vector<std::vector<EPiece>> m_board;
	std::unordered_set<Bridge> m_bridges;
	std::vector<Bridge> m_vBridgeGenerator1;
	std::vector<Bridge> m_vBridgeGenerator2;
	std::vector<Bridge> m_vBridgeGenerator3;
	std::vector<Bridge> m_vBridgeGenerator4;
};

