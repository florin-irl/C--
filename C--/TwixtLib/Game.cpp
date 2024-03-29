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
	: m_player1{ EPiece::RedPeg }
	, m_player2{ EPiece::BlackPeg }
	, m_gameState{ EGameState::Playing }
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

EPiece Game::GetPlayer1() const
{
	return m_player1;
}

EPiece Game::GetPlayer2() const
{
	return m_player2;
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

void Game::ChangePlayer1WithPlayer2()
{
	m_player1 = EPiece::BlackPeg;
	m_player2 = EPiece::RedPeg;
}

void Game::PlacePeg(int line, int column)
{
	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t place pegs anymore !");

	if (m_pegPlaced)
		throw CantPlaceMoreThanOnePegException("You can't place more than 1 peg in a turn !");

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
	if (m_gameState != EGameState::Playing)
		throw GameOverException("The game is over ! You can t place bridges anymore !");

	m_board->PlaceBridge(firstLine, firstColumn, secondLine, secondColumn); // This can Throw Exception //
	if (m_board->GetTurn() == EPiece::RedPeg)
		m_redBridgesRemaining--;
	else
		m_blackBridgesRemaining--;

	ChangeStateIfGameWon(firstLine, firstColumn);
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

	if (!m_pegPlaced)
		throw MustPlacePegBeforeSwitchingTurnException("You must place a peg before switching turn !");

	m_board->SwitchTurn();
	m_pegPlaced = false;
}

void Game::SaveGame(const std::string& fileName) const
{
	std::ofstream fout(fileName);
	if (!fout.is_open())
	{
		return;
	}

	// Write Player1 and Player2 //
	fout << static_cast<int>(m_player1) << " " << static_cast<int>(m_player2) << std::endl;

	// Write Game State //
	fout<< static_cast<int>(m_gameState) << std::endl;

	// Write Turn //
	fout << static_cast<int>(m_board->GetTurn()) << std::endl;

	// Write BoardSize //
	fout << m_board->GetBoardSize() << std::endl;

	// Write NrPegs and NrBridges //
	fout << m_nrPegs << " " << m_nrBridges << std::endl;

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
	}

	std::ostringstream boardString;

	// Read Player1 and Player2 //
	int player1, player2;
	fin >> player1 >> player2;
	m_player1 = static_cast<EPiece>(player1);
	m_player2 = static_cast<EPiece>(player2);

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

	// Read NrPegs and NrBridges //
	fin >> m_nrPegs >> m_nrBridges;

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
	// Reset Players //
	m_player1 = EPiece::RedPeg;
	m_player2 = EPiece::BlackPeg;
	
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
	if (m_redPegsRemaining == 0 && m_blackPegsRemaining == 0)
		m_gameState = EGameState::Draw;
}

void Game::ChangeStateIfGameWon(int line, int column)
{
	if (m_board->CheckGameWon(line, column))
		m_gameState = (m_board->GetTurn() == EPiece::RedPeg) ? EGameState::WonByRed : EGameState::WonByBlack;
}
