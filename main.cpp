#include "mapcreate.h"

int main()
{
	bool running = true;
	map wump;
	while (running)
	{
		GameStates state = GameStates::PLAYING;
		wump.printplayer();
		wump.moveplayer();
		if (wump.question())
		{
			state = GameStates::EXIT;
		}

		std::cout << "\n";
		switch (state)
		{
		case GameStates::EXIT:
			running = false;
			break;
		default:
			break;
		}
	}

	std::cout << "GAME OVER\n";
	system("pause");
	return 0;
}