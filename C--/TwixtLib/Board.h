#pragma once
#include "IBoard.h"
#include <vector>
#include <unordered_set>
#include <list>

// Hash function for : std::unordered_set<Bridge> m_bridges; //

namespace std {
	template <>
	struct hash<Position> {
		std::size_t operator()(const Position& pos) const {
			return std::hash<int>()(pos.GetRow()) ^ (std::hash<int>()(pos.GetCol()) << 1);
		}
	};

	template <>
	struct hash<Bridge> {
		std::size_t operator()(const Bridge& bridge) const {
			// Use the hash functions for Position to hash the Bridge
			return hash<Position>()(bridge.GetFirstPegPos()) ^ (hash<Position>()(bridge.GetSecondPegPos()) << 1);
		}
	};
}

// Board Class //

class Board : public IBoard
{
public:
	Board();
	Board(int boardSize);

	void SetBoardSize(int boardSize) override;

	int GetBoardSize() const override;
	EPiece GetTurn() const override;
	EPiece GetPiece(int line, int column) const override;
	std::vector<std::vector<EPiece>> GetBoard() const override;
	std::unordered_set<Bridge> GetBridges() const override;

	void PlacePeg(int line, int column) override;
	void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;
	void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) override;
	bool CheckGameWon(int line, int column) override;
	void SwitchTurn() override;

	void LoadBoard(const std::ostringstream& stringBoard) override;
	void ResetBoard() override;

private:
	int m_boardSize;
	EPiece m_turn;

	std::vector<std::vector<EPiece>> m_board;
	std::unordered_set<Bridge> m_bridges;

	std::vector<Bridge> m_vBridgeGenerator1;	// (2, 1) = +2 linii, +1 coloana //
	std::vector<Bridge> m_vBridgeGenerator2;	// (2,-1) //
	std::vector<Bridge> m_vBridgeGenerator3;	// (1,-2) //
	std::vector<Bridge> m_vBridgeGenerator4;	// (1, 2) //

	void ResizeBoard(int boardSize);
	void InitializeBoard();
	void InitializeBridgeGenerators();
	void InitializeBridgeGenerator1();
	void InitializeBridgeGenerator2();
	void InitializeBridgeGenerator3();
	void InitializeBridgeGenerator4();

	std::list<Position> GetValidPegs(int line, int column);
};

