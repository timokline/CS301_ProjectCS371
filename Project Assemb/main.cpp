#include "mapcreate.h"

int main()
{
	map wump;
	std::string answer;

	while (0 == 0)
	{
		wump.printplayer();
		wump.detect();
		std::cout << "Would you like to move or shoot? ";
		std::cin >> answer;

		if (answer == "move")
		{
			wump.moveplayer();
		}

		if (answer == "shoot")
		{
			if (wump.shoot() == 0)
			{
				std::cout << "You missed.\n";
			}
			else
			{
				std::cout << "You killed the Wumpus and won!";
				return 0;
			}
		}

		wump.wumpmove();

		if (wump.dead() == 1)
		{
			return 0;
		}


		std::cout << "\n";
	}


}