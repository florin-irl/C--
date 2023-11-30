#include "Game.h"
#include "GameExceptions.h"

IGamePtr IGame::CreateGame()
{
	return std::make_shared<Game>();
}

Game::Game(int boardSize, int nrPegs, int nrBridges)
	: m_boardSize{ boardSize }
	, m_gameState{ EGameState::Playing }
	, m_redPegsRemaining{ nrPegs }
	, m_redBridgesRemaining{ nrBridges }
	, m_blackPegsRemaining{ nrPegs }
	, m_blackBridgesRemaining{ nrBridges }
{
	m_board = IBoard::CreateBoard();
}

EPiece Game::GetTurn() const
{
	return m_board->GetTurn();
}

EGameState Game::GetGameState() const
{
	return m_gameState;
}

std::unordered_set<Bridge> Game::GetBridges()
{
	return m_board->GetBridges();
}
