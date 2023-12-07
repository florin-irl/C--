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

int main()
{
	return 0;
}