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