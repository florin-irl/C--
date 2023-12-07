#include <iostream>
#include "IGame.h"
#include "GameExceptions.h"

void DisplayBridges(const std::unordered_set<Bridge>& bridges)
{
	for (const auto& bridge : bridges)
	{
		std::cout << "(" << bridge.GetFirstPegPos().GetRow() << "," << bridge.GetFirstPegPos().GetCol() << ") -> ";
		std::cout << "(" << bridge.GetSecondPegPos().GetRow() << "," << bridge.GetSecondPegPos().GetCol() << ")\n";
	}
}

void DispayBoard(const IGamePtr& game)
{
	for (int i = 0; i < 24; i++)
	{
		std::cout << "                    ";
		for (int j = 0; j < 24; j++)
		{
			if ((i == 0 && j == 0) || (i == 0 && j == 23) || (i == 23 && j == 0) || (i == 23 && j == 23))
				std::cout << "   ";
			else
			{
				if (game->GetPiece(i, j) == EPiece::RedPeg)
					std::cout << " *";
				else if (game->GetPiece(i, j) == EPiece::BlackPeg)
					std::cout << " #";
				else std::cout << " .";
				if ((j == 0 || j == 22) && i != 0 && i != 23)
					std::cout << "|";
			}
		}
		
	}
	//TO UPDATE
}

int main()
{
	return 0;
}