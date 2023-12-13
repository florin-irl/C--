#include "gtest/gtest.h"

#include "Game.h"
#include "GameExceptions.h"
TEST(GameTurnManagement, FirstGameTurn)
{
	Game g;
	EXPECT_EQ(g.GetTurn(), EPiece::RedPeg);
}

TEST(GameTurnManagement, SwitchGameTurn)
{
	Game g;
	g.SwitchTurn();
	EXPECT_EQ(g.GetTurn(), EPiece::BlackPeg);
}

//?
TEST(InitialGameBoard, AllGameHolesEmpty)
{
	Game g;
	for (size_t i = 0; i < 24; i++)
	{
		for (size_t j = 0; j < 24; j++)
		{
			EXPECT_EQ(g.GetPiece(i, j), EPiece::None);
		}
	}
}

TEST(GameState, StartingGameState)
{
	Game g;
	EXPECT_EQ(g.GetGameState(), EGameState::Playing);
}

TEST(GamePlacePeg, PlaceRedPeg)
{
	Game g;
	g.PlacePeg(5, 19);
	EXPECT_EQ(g.GetPiece(5, 19), EPiece::RedPeg);
}

TEST(GamePlacePeg, PlaceBlackPeg)
{
	Game g;
	g.PlacePeg(10, 16);
	g.SwitchTurn();
	g.PlacePeg(4, 7);
	EXPECT_EQ(g.GetPiece(4, 7), EPiece::BlackPeg);
}

//??
TEST(GamePlacePeg, PlacePegWhenGameOver)
{
	Game g;
	if (g.GetGameState() != EGameState::Playing)
	{
		EXPECT_THROW(g.PlacePeg(2, 9), GameOverException);
	}
	g.SwitchTurn();
	if (g.GetGameState() != EGameState::Playing)
	{
		EXPECT_THROW(g.PlacePeg(7, 15), GameOverException);
	}
}