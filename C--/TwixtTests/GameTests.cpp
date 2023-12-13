#include "gtest/gtest.h"

#include "Game.h"
#include "Board.h"
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
TEST(GameFunctions, TestFuncitonAfterGameOver)
{
	//TO DO 
}


TEST(GamePlaceBridge, PlaceRedBridge) //xhash file error
{
	Game g;
	g.PlacePeg(16, 19);
	g.SwitchTurn();
	g.PlacePeg(4, 5);
	g.SwitchTurn();
	g.PlacePeg(18, 18);
	g.PlaceBridge(16, 19, 18, 18);
	
	const Bridge redBridge({ 18, 18 } , { 16, 19 } );
	const auto bridges = g.GetBridges();
	const auto it = bridges.find(redBridge);
	EXPECT_EQ(*it, redBridge);
}

TEST(GamePlaceBridge, PlaceBlackBridge)
{
	Game g;
	g.PlacePeg(16, 19);
	g.SwitchTurn();
	g.PlacePeg(4, 5);
	g.SwitchTurn();
	g.PlacePeg(18, 18);
	g.SwitchTurn();
	g.PlacePeg(5, 3);

	g.PlaceBridge(4, 5, 5, 3);
	const Bridge blackBridge({ 4,5 }, { 5,3 });
	const auto bridges = g.GetBridges();
	const auto it = bridges.find(blackBridge);
	EXPECT_EQ(*it, blackBridge);
}
