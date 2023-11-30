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

void Game::PlacePeg(int line, int column)
{
	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t place pegs anymore !");

	m_board->PlacePeg(line, column); // This can Throw Exception //
	if (m_board->GetTurn() == EPiece::RedPeg)
		m_redPegsRemaining--;
	else
		m_blackPegsRemaining--;
	ChangeStateIfDraw();
}

void Game::PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t place bridges anymore !");

	m_board->PlaceBridge(firstLine, firstColumn, secondLine, secondColumn); // This can Throw Exception //
	if (m_board->GetTurn() == EPiece::RedPeg)
		m_redBridgesRemaining--;
	else
		m_blackBridgesRemaining--;

	int lineToVerify = -1;
	int columnToVerify = -1;

	if (firstLine == 0 || firstLine == m_boardSize - 1 || firstColumn == 0 || firstColumn == m_boardSize - 1)
	{
		lineToVerify = firstLine;
		columnToVerify = firstColumn;
	}
	else if (secondLine == 0 || secondLine == m_boardSize - 1 || secondColumn == 0 || secondColumn == m_boardSize - 1)
	{
		lineToVerify = secondLine;
		columnToVerify = secondColumn;
	}

	if (lineToVerify != -1 && columnToVerify != -1)
		ChangeStateIfGameWon(lineToVerify, columnToVerify);

	ChangeStateIfDraw();
}

void Game::ChangeStateIfDraw()
{
	if (m_redPegsRemaining == 0 && m_redBridgesRemaining == 0
		&& m_blackPegsRemaining == 0 && m_blackBridgesRemaining == 0
		&& m_gameState == EGameState::Playing
		)
		m_gameState = EGameState::Draw;
}

void Game::ChangeStateIfGameWon(int line, int column)
{
	if (m_board->CheckGameWon(line, column) == true)
		m_gameState = (m_board->GetTurn() == EPiece::RedPeg) ? EGameState::WonByRed : EGameState::WonByBlack;
}