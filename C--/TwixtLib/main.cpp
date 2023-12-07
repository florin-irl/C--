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
		std::cout << std::endl;
		if (i == 0 || i == 22)
		{
			std::cout << "                      ";
			std::cout << "==============================================\n";
		}
	}
	std::unordered_set<Bridge> bridges = game->GetBridges();
	DisplayBridges(bridges);
}

void PlayOption(int option, IGamePtr& game)
{
	int firstLine, firstColumn, secondLine, secondColumn;
	switch (option) {
	case 1:
		std::cout << "Line : ";
		std::cin >> firstLine;
		std::cout << "Column : ";
		std::cin >> firstColumn;
		try
		{
			game->PlacePeg(firstLine, firstColumn);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		break;
	case 2:
		std::cout << "First line : ";
		std::cin >> firstLine;
		std::cout << "First column : ";
		std::cin >> firstColumn;

		std::cout << "Second line : ";
		std::cin >> secondLine;
		std::cout << "Second column : ";
		std::cin >> secondColumn;

		try
		{
			game->PlaceBridge(firstLine, firstColumn, secondLine, secondColumn);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		break;

	case 3:
		std::cout << "First line : ";
		std::cin >> firstLine;
		std::cout << "First column : ";
		std::cin >> firstColumn;

		std::cout << "Second line : ";
		std::cin >> secondLine;
		std::cout << "Second column : ";
		std::cin >> secondColumn;

		try
		{
			game->RemoveBridge(firstLine, firstColumn, secondLine, secondColumn);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		break;

	case 4:
		try
		{
			game->SwitchTurn();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		break;
	default:
		std::cout << "Your option is not valid !";
		break;
	}
}

int main()
{
	return 0;
}