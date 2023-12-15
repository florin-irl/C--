#pragma once

#include "EPiece.h"
#include "Bridge.h"
#include <unordered_set>
#include <memory>
#include <sstream>

using IBoardPtr = std::shared_ptr<class IBoard>;

class IBoard
{
public:
	static IBoardPtr CreateBoard();
	virtual int GetBoardSize() const = 0;
	virtual EPiece GetTurn() const = 0;
	virtual EPiece GetPiece(int line, int column) const = 0;
	virtual std::vector<std::vector<EPiece>> GetBoard() const = 0;
	virtual std::unordered_set<Bridge> GetBridges() const = 0;
	virtual void PlacePeg(int line, int column) = 0;
	virtual void PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0;
	virtual void RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn) = 0;
	virtual bool CheckGameWon(int line, int column) = 0;
	virtual void SwitchTurn() = 0;
	virtual void LoadBoard(const std::ostringstream& stringBoard) = 0;
	virtual void ResetBoard() = 0;
	virtual ~IBoard() = default;
};

