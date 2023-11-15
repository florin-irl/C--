#pragma once
#include "IBoard.h"
#include "EPiece.h"
#include "Bridge.h"
#include <vector>
#include <unordered_set>

class Board : public IBoard
{
public:
	Board();
	Board(int boardSize);

	EPiece GetPiece(int line, int column) const override;
	std::unordered_set<Bridge> GetBridges() const override;
	void PlacePeg(int line, int column);
	void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;
	void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;
	bool CheckGameWon(int line, int column) override;
	void SwitchTurn() override;
private:
	int m_boardSize;
	EPiece m_turn;
	std::vector<std::vector<EPiece>> m_board;
	std::unordered_set<Bridge> m_bridges;
	std::vector<Bridge> m_vBridgeGenerator1;
	std::vector<Bridge> m_vBridgeGenerator2;
	std::vector<Bridge> m_vBridgeGenerator3;
	std::vector<Bridge> m_vBridgeGenerator4;

	void InitializeBoard(int boardSize);
	void InitializeBridgeGenerators();
	void InitializeBridgeGenerator1();
	void InitializeBridgeGenerator2();
	void InitializeBridgeGenerator3();
	void InitializeBridgeGenerator4();

};

