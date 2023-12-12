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

TEST(PlacePeg, PlacePegOnOccupiedPosition)
{
	Board b;
	b.PlacePeg(5, 7);
	EXPECT_THROW(b.PlacePeg(5, 7), OcuppiedPositionException);
	b.SwitchTurn();
	b.PlacePeg(10, 15);
	EXPECT_THROW(b.PlacePeg(10, 15), OcuppiedPositionException);
}

//Bridge Tests

TEST(PlaceBridge, PlaceRedBridge)
{
	Board b;
	b.PlacePeg(7,8);
	b.PlacePeg(8, 10);
	b.PlaceBridge(7, 8, 8, 10);
	Bridge firstBridge({ 7,8 }, { 8,10 });
	EXPECT_EQ(*(b.GetBridges().find(firstBridge)), firstBridge);	
}

TEST(PlaceBridge, PlaceBlackBridge)
{
	Board b;
	b.SwitchTurn();
	b.PlacePeg(19, 17);
	b.PlacePeg(18, 15);
	b.PlaceBridge(19, 17, 18, 15);
	Bridge firstBridge({ 18,15 }, { 19,17 });
	EXPECT_EQ(*(b.GetBridges().find(firstBridge)), firstBridge);
}
//?
TEST(PlaceBridge, PlaceBridgeOutsideTable)
{
	Board b;
	b.PlacePeg(8, 20);
	b.PlacePeg(9, 18);
	EXPECT_THROW(b.PlaceBridge(-3, 29, -14, 33),OutOfBoundsException);
}

TEST(PlaceBridge, PlaceBridgeInPositionsThatDontFormBridge)
{
	Board b;
	b.PlacePeg(2, 7);
	b.PlacePeg(9, 16);
	EXPECT_THROW(b.PlaceBridge(2, 7, 9, 16), CantFormBridgeException);
}

TEST(PlaceBridge, PlaceBridgeUsingDifferentColorPegs)
{
	Board b;
	b.PlacePeg(15, 9);
	b.SwitchTurn();
	b.PlacePeg(16, 7);
	EXPECT_THROW(b.PlaceBridge(15, 9, 16, 7), InvalidPegsForBridgeException);
}

TEST(PlaceBridge, PlaceBridgeInABlockedPosition)
{
	Board b;
	b.PlacePeg(21, 13);
	b.PlacePeg(19, 14);
	b.PlaceBridge(19, 14, 21, 13);
	b.PlacePeg(21, 14);
	b.PlacePeg(20, 12);
	EXPECT_THROW(b.PlaceBridge(21, 14, 20, 12), BridgeInTheWayException);
}