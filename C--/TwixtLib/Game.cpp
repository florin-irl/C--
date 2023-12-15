#include "Game.h"
#include "GameExceptions.h"
#include <fstream>
#include <sstream>

IGamePtr IGame::CreateGame()
{
	return std::make_shared<Game>();
}

Game::Game()
	: Game(24, 50, 50)
{}

Game::Game(int boardSize, int nrPegs, int nrBridges)
	: m_gameState{ EGameState::Playing }
	, m_nrPegs{ nrPegs }
	, m_nrBridges{ nrBridges }
	, m_redPegsRemaining{ nrPegs }
	, m_redBridgesRemaining{ nrBridges }
	, m_blackPegsRemaining{ nrPegs }
	, m_blackBridgesRemaining{ nrBridges }
	, m_pegPlaced{ false }
{
	m_board = IBoard::CreateBoard();
	m_board->SetBoardSize(boardSize);
}

int Game::GetBoardSize() const
{
	return m_board->GetBoardSize();
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

	if (firstLine == 0 || firstLine == m_board->GetBoardSize() - 1 || firstColumn == 0 || firstColumn == m_board->GetBoardSize() - 1)
	{
		lineToVerify = firstLine;
		columnToVerify = firstColumn;
	}
	else if (secondLine == 0 || secondLine == m_board->GetBoardSize() - 1 || secondColumn == 0 || secondColumn == m_board->GetBoardSize() - 1)
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
	fout << m_board->GetBoardSize() << std::endl;

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
	for (int i=0; i < m_board->GetBoardSize(); i++)
	{
		for (int j = 0; j < m_board->GetBoardSize(); j++)
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
	std::ifstream fin(fileName);
	if (!fin.is_open())
	{
		return;
		// Throw Exception //
	}

	std::ostringstream boardString;

	// Read Game State //
	int state;
	fin >> state;
	m_gameState = static_cast<EGameState>(state);

	// Read Turn //
	int turn;
	fin >> turn;
	boardString << turn << std::endl;

	// Read Board Size //
	int boardSize;
	fin >> boardSize;
	boardString << boardSize << std::endl;

	// Read Red Pegs Remaining //
	fin >> m_redPegsRemaining;

	// Read Red Bridges Remaining //
	fin >> m_redBridgesRemaining;

	// Read Black Pegs Remaining //
	fin >> m_blackPegsRemaining;

	// Read Black Bridges Remaining //
	fin >> m_blackBridgesRemaining;

	// Read PegPlaced value //
	fin >> m_pegPlaced;

	// Read Board //
	int piece;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			fin >> piece;
			boardString << piece << " ";
		}			
		boardString << std::endl;
	}

	// Read Bridges //
	int firstRow, firstCol, secondRow, secondCol;
	while (fin >> firstRow >> firstCol >> secondRow >> secondCol)
	{
		boardString << firstRow << " " << firstCol << " " << secondRow << " " << secondCol << std::endl;
	}

	// Load Board Using boardString //
	m_board->LoadBoard(boardString);

	fin.close();
}

void Game::RestartGame()
{
	// Reset Game State //
	m_gameState = EGameState::Playing;

	// Reset Board //
	m_board->ResetBoard();

	// Reset Number of Red Pegs Remaining //
	m_redPegsRemaining = m_nrPegs;

	// Reset Number of Red Bridges Remaining //
	m_redBridgesRemaining = m_nrBridges;

	// Reset Number of Black Pegs Remaining //
	m_blackPegsRemaining = m_nrPegs;

	// Reset Number of Black Bridges Remaining //
	m_blackBridgesRemaining = m_nrBridges;

	// Reset Peg Placed property //
	m_pegPlaced = false;
}

void Game::SetUpGame(int boardSize, int nrPegs, int nrBridges)
{
	m_board->SetBoardSize(boardSize);
	m_nrPegs = nrPegs;
	m_nrBridges = nrBridges;
	RestartGame();
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
