#include "gtest/gtest.h"

#include "Game.h"
#include "Board.h"
#include"GameExceptions.h"

TEST(InitialBoard, AllHolesEmpty)
{
	Board b;

	for (size_t i = 0; i < 24; i++)
	{
		for (size_t j = 0; j < 24; j++)
		{
			EXPECT_EQ(b.GetPiece(i, j), EPiece::None);
		}
	}
}

TEST(InitialBoard, FirstTurn)
{
	Board b;

	EXPECT_EQ(b.GetTurn(), EPiece::RedPeg);
}

TEST(TurnManagement, SwitchTurn)
{
	Board b;

	EXPECT_EQ(b.GetTurn(), EPiece::RedPeg);
	b.SwitchTurn();
	EXPECT_EQ(b.GetTurn(), EPiece::BlackPeg);

}

TEST(TurnManagement, PlaceOnlyPegPerTurn)
{
	Board b;

	b.PlacePeg(5, 9);
	EXPECT_THROW(b.PlacePeg(2, 17), TwixtException);
}

TEST(PlacePeg, PlaceRedPeg)
{
	Board b;
	b.PlacePeg(1, 1);
	EXPECT_EQ(b.GetPiece(1, 1), EPiece::RedPeg);

}

TEST(PlacePeg, PlaceBlackPeg)
{
	Board b;
	b.SwitchTurn();
	b.PlacePeg(3, 4);
	EXPECT_EQ(b.GetPiece(3, 4), EPiece::BlackPeg);
}

TEST(PlacePeg, PlacePegOnRedEdge)
{
	Board b;
	b.PlacePeg(0, 2);
	b.PlacePeg(23, 4);
	EXPECT_EQ(b.GetPiece(0, 2), EPiece::RedPeg);
	EXPECT_EQ(b.GetPiece(23, 4), EPiece::RedPeg);
}

TEST(PlacePeg, PlacePegOnBlackEdge)
{
	Board b;
	b.SwitchTurn();
	b.PlacePeg(13, 0);
	b.PlacePeg(20, 23);
	EXPECT_EQ(b.GetPiece(13, 0), EPiece::BlackPeg);
	EXPECT_EQ(b.GetPiece(20, 23), EPiece::BlackPeg);
}