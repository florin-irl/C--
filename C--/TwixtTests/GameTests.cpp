#include "gtest/gtest.h"

#include "Game.h"
#include "Board.h"
#include"GameExceptions.h"

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

TEST(InitialGameBoard, InitialBoardPieces)
{
    Game g;
    EXPECT_EQ(g.GetNrBlackPegsRemaining(), 50);
    EXPECT_EQ(g.GetNrRedPegsRemaining(), 50);
    EXPECT_EQ(g.GetNrBlackBridgesRemaining(), 50);
    EXPECT_EQ(g.GetNrRedBridgesRemaining(), 50);
}


TEST(InitialBoardGame, CustomBoardSize)
{
    Game g;
    g.SetUpGame(15, 50, 50);
    EXPECT_EQ(g.GetBoardSize(), 15);
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