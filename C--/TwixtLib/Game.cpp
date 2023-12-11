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

EPiece Game::GetPiece(int line, int column) const
{
	return m_board->GetPiece(line, column);
}

std::unordered_set<Bridge> Game::GetBridges() const
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

	if (m_gameState == EGameState::Playing)
		ChangeStateIfDraw();
}

void Game::RemoveBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t remove bridges anymore !");

	m_board->RemoveBridge(firstLine, firstColumn, secondLine, secondColumn); // This can Throw Exception //
	if (m_board->GetTurn() == EPiece::RedPeg)
		m_redBridgesRemaining++;
	else
		m_blackBridgesRemaining++;
}

bool Game::IsGameOver() const
{
	if (m_gameState == EGameState::WonByRed || m_gameState == EGameState::WonByBlack || m_gameState == EGameState::Draw)
		return true;
	return false;
}

void Game::SwitchTurn()
{
	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t switch turn anymore !");
	m_board->SwitchTurn();
}

void Game::SaveGame(std::ofstream& out) const
{
	//write game state
	out << static_cast<int>(m_gameState) << std::endl;
	//write board size
	out << m_boardSize << std::endl;
	//write board
	for (int i=0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
			out << static_cast<int>(m_board->GetPiece(i, j));
		out << std::endl;
	}
	//write red Pegs remaining
	out << m_redPegsRemaining << std::endl;
	//write red Bridges remaining
	out << m_redBridgesRemaining << std::endl;
	//write black Pegs remaining
	out << m_blackPegsRemaining << std::endl;
	//write black Bridges remaining
	out << m_blackBridgesRemaining << std::endl;
	
}

void Game::LoadGame(std::istream& in)
{
	//read game state
	int gameStateInt;
	in >> gameStateInt;
	EGameState gameState = static_cast<EGameState>(gameStateInt);
	m_gameState = gameState;
	//read board size;
	int boardSize;
	in >> boardSize;
	m_boardSize = boardSize;
	//read board
	int pieceInt;
	for(int i=0;i<m_boardSize;i++)
		for (int j = 0; j < m_boardSize; j++)
		{
			in >> pieceInt;
			EPiece piece = static_cast<EPiece>(pieceInt);
			m_board->GetBoard()[i][j] = piece;
		}
	//read remaining red pegs
	int remainingRedPegs;
	in >> remainingRedPegs;
	m_redPegsRemaining = remainingRedPegs;
	//read remaining red bridges
	int remainingRedBridges;
	in >> remainingRedBridges;
	m_redBridgesRemaining = remainingRedBridges;
	//read remaining black pegs;
	int remainingBlackPegs;
	in >> remainingBlackPegs;
	m_blackPegsRemaining = remainingBlackPegs;
	//read remaining black bridges;
	int remainingBlackBridges;
	in >> remainingBlackBridges;
	m_blackBridgesRemaining = remainingBlackBridges;

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
