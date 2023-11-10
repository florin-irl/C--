#include "Game.h"

Game::Game(int boardSize, int nrPegs, int nrBridges)
	:m_boardSize{ boardSize }
	, m_redPegsRemaining{ nrPegs }
	, m_blackPegsRemaining{ nrPegs }
	, m_redBridgesRemaining{ nrBridges }
	, m_blackBridgesRemaining{ nrBridges }
{
}
