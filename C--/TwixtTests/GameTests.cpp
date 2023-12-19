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
	g.PlacePeg(6, 7);
	g.SwitchTurn();
	EXPECT_EQ(g.GetTurn(), EPiece::BlackPeg);
}

TEST(GameTurnManagement, SwitchTurnBeforePlacingPeg)
{
	Game g;
	EXPECT_THROW(g.SwitchTurn(), MustPlacePegBeforeSwitchingTurnException);
}

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

TEST(InitialGameBoard, InitialBoardSize)
{
	Game g;
	EXPECT_EQ(g.GetBoardSize(), 24);
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

TEST(GamePlacePeg, PlaceMoreThanOnePegPerTurn)
{
	Game g;
	g.PlacePeg(18, 9);
	EXPECT_THROW(g.PlacePeg(3, 16), CantPlaceMoreThanOnePegException);
}

//??
TEST(GameFunctions, TestFunctionAfterGameOver)
{
	Game g;
	EXPECT_EQ(g.IsGameOver(), false);
	g.SetUpGame(7, 50, 50);
	g.PlacePeg(0, 1);
	g.SwitchTurn();
	g.PlacePeg(3, 0);
	g.SwitchTurn();
	g.PlacePeg(2, 2);
	g.PlaceBridge(0, 1, 2, 2);
	g.SwitchTurn();
	g.PlacePeg(4, 2);
	g.PlaceBridge(3, 0, 4, 2);
	g.SwitchTurn();
	g.PlacePeg(4, 3);
	g.PlaceBridge(2, 2, 4, 3);
	g.SwitchTurn();
	g.PlacePeg(3, 4);
	g.SwitchTurn();
	g.PlacePeg(6, 4);
	g.PlaceBridge(4, 3, 6, 4);
	
	EXPECT_EQ(g.GetGameState(), EGameState::WonByRed);
	EXPECT_EQ(g.IsGameOver(), true);
	EXPECT_THROW(g.PlacePeg(0, 3), GameOverException);
	EXPECT_THROW(g.PlaceBridge(0, 1, 2, 2), GameOverException);
	EXPECT_THROW(g.RemoveBridge(2, 2, 4, 3), GameOverException);
	EXPECT_THROW(g.SwitchTurn(), GameOverException);
}


TEST(GamePlaceBridge, PlaceRedBridge) 
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

TEST(GameRemoveBridge, RemoveRedBridge)
{
	Game g;
	g.PlacePeg(6, 17);
	g.SwitchTurn();
	g.PlacePeg(20, 22);
	g.SwitchTurn();
	g.PlacePeg(8, 16);
	g.PlaceBridge(6, 17, 8, 16);
	Bridge redBridge({ 6,17 }, { 8,16 });
	g.RemoveBridge(6, 17, 8, 16);
	auto Bridges = g.GetBridges();
	EXPECT_EQ(Bridges.find(redBridge), Bridges.end());

}

TEST(GameRemoveBridge, RemoveBlackBridge)
{
	Game g;
	g.PlacePeg(6, 20);
	g.SwitchTurn();
	g.PlacePeg(4, 6);
	g.SwitchTurn();
	g.PlacePeg(19, 4);
	g.SwitchTurn();
	g.PlacePeg(3, 8);
	g.PlaceBridge(4, 6, 3, 8);

	Bridge blackBridge({ 4,6 }, { 3,8 });
	g.RemoveBridge(4, 6, 3, 8);
	auto Bridges = g.GetBridges();
	EXPECT_EQ(Bridges.find(blackBridge), Bridges.end());

}