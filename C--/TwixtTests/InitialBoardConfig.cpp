#include "gtest/gtest.h"

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

TEST(SwitchTurn, SwitchTurn)
{
	Board b;

	EXPECT_EQ(b.GetTurn(), EPiece::RedPeg);
	b.SwitchTurn();
	EXPECT_EQ(b.GetTurn(), EPiece::BlackPeg);

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

TEST(PlacePeg, PlaceRedPegOnOppositeEdge)
{
	Board b;
	EXPECT_THROW(b.PlacePeg(17, 0), EnemyBaseException);
	EXPECT_EQ(b.GetPiece(17, 0), EPiece::None);
	EXPECT_THROW(b.PlacePeg(9, 23), EnemyBaseException);
	EXPECT_EQ(b.GetPiece(9, 23), EPiece::None);
}

TEST(PlacePeg, PlaceBlackPegOnOppositeEdge)
{
	Board b;
	b.SwitchTurn();
	EXPECT_THROW(b.PlacePeg(0, 7), EnemyBaseException);
	EXPECT_EQ(b.GetPiece(0, 7), EPiece::None);
	EXPECT_THROW(b.PlacePeg(23, 16), EnemyBaseException);
	EXPECT_EQ(b.GetPiece(23, 16), EPiece::None);
}

TEST(PlacePeg, PlacePegOutsideTable)
{
	Board b;
	EXPECT_THROW(b.PlacePeg(-4, 27), OutOfBoundsException);
	b.SwitchTurn();
	EXPECT_THROW(b.PlacePeg(19, 30), OutOfBoundsException);
}