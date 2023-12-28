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