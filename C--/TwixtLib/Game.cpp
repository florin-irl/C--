#include "Game.h"
#include "GameExceptions.h"

IGamePtr IGame::CreateGame()
{
	return std::make_shared<Game>();
}

Game::Game()
	: Game(24, 50, 50)
{}

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

void Game::ChangeStateIfDraw()
{
	if (m_redPegsRemaining == 0 && m_redBridgesRemaining == 0
		&& m_blackPegsRemaining == 0 && m_blackBridgesRemaining == 0
		&& m_gameState == EGameState::Playing
		)
		m_gameState = EGameState::Draw;
}