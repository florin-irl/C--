#include "Game.h"
#include "GameExceptions.h"
#include <fstream>

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
	, m_pegPlaced{ false }
{
	m_board = IBoard::CreateBoard();
}

int Game::GetBoardSize() const
{
	return m_boardSize;
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

int Game::GetNrRedPegsRemaining() const
{
	return m_redPegsRemaining;
}

int Game::GetNrRedBridgesRemaining() const
{
	return m_redBridgesRemaining;
}

int Game::GetNrBlackPegsRemaining() const
{
	return m_blackPegsRemaining;
}

int Game::GetNrBlackBridgesRemaining() const
{
	return m_blackBridgesRemaining;
}

void Game::PlacePeg(int line, int column)
{
	if (
		(m_board->GetTurn() == EPiece::RedPeg && m_redPegsRemaining == 0)
		|| (m_board->GetTurn() == EPiece::BlackPeg && m_blackPegsRemaining == 0)
		)
		throw NoMorePegsException("You have no pegs left !");

	if (m_pegPlaced)
		throw CantPlaceMoreThanOnePegException("You can't place more than 1 peg in a turn !");

	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t place pegs anymore !");

	m_board->PlacePeg(line, column); // This can Throw Exception //

	m_pegPlaced = true;

	if (m_board->GetTurn() == EPiece::RedPeg)
		m_redPegsRemaining--;
	else
		m_blackPegsRemaining--;
	ChangeStateIfDraw();
}

void Game::PlaceBridge(int firstLine, int firstColumn, int secondLine, int secondColumn)
{
	if (
		(m_board->GetTurn() == EPiece::RedPeg && m_redBridgesRemaining == 0)
		|| (m_board->GetTurn() == EPiece::BlackPeg && m_blackBridgesRemaining == 0)
		)
		throw NoMoreBridgesException("You have no bridges left !");

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
	if (!m_pegPlaced)
		throw MustPlacePegBeforeSwitchingTurnException("You must place a peg before switching turn !");

	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t switch turn anymore !");

	m_board->SwitchTurn();
	m_pegPlaced = false;
}

void Game::SaveGame(const std::string& fileName) const
{
	std::ofstream fout(fileName);
	if (!fout.is_open())
	{
		return;
		// Throw Exception //
	}

	// Write Game State //
	fout<< static_cast<int>(m_gameState) << std::endl;

	// Write Turn //
	fout << static_cast<int>(m_board->GetTurn()) << std::endl;

	// Write BoardSize //
	fout << m_boardSize << std::endl;

	// Write Red Pegs Remaining //
	fout << m_redPegsRemaining << " ";

	// Write Red Bridges Remaining //
	fout << m_redBridgesRemaining << std::endl;

	// Write Black Pegs Remaining //
	fout << m_blackPegsRemaining << " ";

	// Write Black Bridges Remaining //
	fout << m_blackBridgesRemaining << std::endl;

	// Write PegPlaced value //
	fout << m_pegPlaced << std::endl;

	// Write Board //
	for (int i=0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
			fout << static_cast<int>(m_board->GetPiece(i, j)) << " ";
		fout << std::endl;
	}

	// Write Bridges //
	for (const auto& bridge : m_board->GetBridges())
	{
		fout << bridge.GetFirstPegPos().GetRow() << " " << bridge.GetFirstPegPos().GetCol() << " "
			<< bridge.GetSecondPegPos().GetRow() << " " << bridge.GetSecondPegPos().GetCol() << std::endl;
	}

	fout.close();
}

void Game::LoadGame(const std::string& fileName)
{
	//std::ifstream fin(fileName);
	//if (!fin.is_open())
	//{
	//	return;
	//	// Throw Exception //
	//}

	//// Read Turn //
	//int turn;
	//fin >> turn;
	//EPiece gameTurn = static_cast<EPiece>(turn);


	//if (m_board->GetTurn() != gameTurn)m_board->SwitchTurn();
	////read board size;
	//int boardSize;
	//in >> boardSize;
	//m_boardSize = boardSize;
	////read board
	//int pieceInt;
	//for(int i=0;i<m_boardSize;i++)
	//	for (int j = 0; j < m_boardSize; j++)
	//	{
	//		in >> pieceInt;
	//		EPiece piece = static_cast<EPiece>(pieceInt);
	//		m_board->GetBoard()[i][j] = piece;
	//	}
	////read remaining red pegs
	//int remainingRedPegs;
	//in >> remainingRedPegs;
	//m_redPegsRemaining = remainingRedPegs;
	////read remaining red bridges
	//int remainingRedBridges;
	//in >> remainingRedBridges;
	//m_redBridgesRemaining = remainingRedBridges;
	////read remaining black pegs;
	//int remainingBlackPegs;
	//in >> remainingBlackPegs;
	//m_blackPegsRemaining = remainingBlackPegs;
	////read remaining black bridges;
	//int remainingBlackBridges;
	//in >> remainingBlackBridges;
	//m_blackBridgesRemaining = remainingBlackBridges;

}

void Game::RestartGame()
{
	// Reset Game State //
	m_gameState = EGameState::Playing;

	// Reset Board //
	m_board->ResetBoard();

	// Reset Number of Red Pegs Remaining //
	m_redPegsRemaining = 50;

	// Reset Number of Red Bridges Remaining //
	m_redBridgesRemaining = 50;

	// Reset Number of Black Pegs Remaining //
	m_blackPegsRemaining = 50;

	// Reset Number of Black Bridges Remaining //
	m_blackBridgesRemaining = 50;

	// Reset Peg Placed property //
	m_pegPlaced = false;
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
