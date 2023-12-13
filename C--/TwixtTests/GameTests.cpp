#include "gtest/gtest.h"

#include "Game.h"

TEST(GameTurnManagement, FirstGameTurn)
{
	Game g;
	EXPECT_EQ(g.GetTurn(), EPiece::RedPeg);
}
