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