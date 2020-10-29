#include "mapcreate.h"

int main()
{
	map wump;
	std::string answer;

	while (0 == 0)
	{
		wump.printplayer();
		wump.moveplayer();

		if (wump.dead() == 1)
		{
			return 0;
		}

		std::cout << "\n";
	}


}