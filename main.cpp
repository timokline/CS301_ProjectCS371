#include "main.h"
#include "characters.h"

////////////////////////////////////////////////////////////
//			In Game Clock 
////////////////////////////////////////////////////////////
class Time
{
public:
	Time()
	{
		begin();
	}
	void begin()
	{
		start = system_clock::now();
	}
	void finish()
	{
		end = system_clock::now();
		std::cout << "Time played: " <<  duration_cast<fsec>(end - start).count() << "sec\n";
	}
private:
	system_clock::time_point start;
	system_clock::time_point end;
	typedef std::chrono::duration<double> fsec;
	typedef std::chrono::duration<double> fms;
};

////////////////////////////////////////////////////////////
//			Out of combat potion funtion  
////////////////////////////////////////////////////////////
bool usePotions(Player &player)
{
	if (player.potions > 0)
	{
		int x = 0;
		std::string input;
		std::cout << "HP: [" << player.playerhp << "]\n";
		std::cout << "You have " << player.potions << " potions.\n";
		std::cout << "Would you like to use a potion to heal yourself? [Y/N] ";
		while (std::getline(std::cin, input))
		{
			std::istringstream instream(input);
			instream >> input;
			if (!instream)
			{
				std::cout << "Please enter Y or N: ";
				continue;
			}
			std::transform(input.begin(), input.end(), input.begin(),
				[](unsigned char c) { return std::tolower(c); });
			if (input == "y")
			{
				return 1;
			}
			else if (input == "n")
			{
				break;
			}
			else
			{
				std::cout << "Not a viable answer: ";
			}
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////
//			Main Game loop 
////////////////////////////////////////////////////////////
int main()
{
	//Game Startup player settings
	const int MAX_HP = 150;
	Player playertemp;
	playertemp.playerhp = MAX_HP;
	playertemp.potions = 5;
	playertemp.difficulty = 0;
	playertemp.fire = 1;
	playertemp.grass = 1;
	playertemp.water = 1;
	playertemp.key = 1;
	playertemp.blockcd = 0;
	//std::cout << "zp";

	//initial map/timer creation
	map* floor = new map(playertemp);
	Time t;
	bool running = true;

	//Main Game loop
	while (running)
	{
		GameStates state = GameStates::PLAYING;
		

		//Calling the floor's player movement funtion
		std::cout << "--------------------------------\n";
		floor->printplayer();
		floor->moveplayer();
		std::cout << "\n--------------------------------\n";

		//Encounter determiner
		playertemp.playerhp = floor->question(playertemp);

		//End of floor code to move on to next floor or end the game
		if (floor->bossdead()  || playertemp.playerhp <= 0)
		{
			//End game as you or final boss is dead
			if (playertemp.difficulty || playertemp.playerhp <= 0)
			{
				t.finish();
				state = GameStates::EXIT;
			}
			//Next floor
			else
			{
				std::cout << "\nThe figure retreats, but is this the end?\nYou proceed down the stairs.\n";
				playertemp.difficulty += 1;
				playertemp.key = 0;
				delete floor;
				map* floor = new map(playertemp);
			}
		}

		//Ending the game
		switch (state)
		{
		case GameStates::EXIT:
			running = false;
			break;
		default:
			//Using potion game loop function
			if (usePotions(playertemp))
			{
				if (playertemp.playerhp < MAX_HP)
				{
					playertemp.potions = playertemp.potions - 1;
					if (playertemp.playerhp > 100)
						playertemp.playerhp = MAX_HP;
					else
						playertemp.playerhp += 50;
					std::cout << "You have " << playertemp.potions << " potions left.\n";
				}
				else
					std::cout << "You have full health.\n";
			}
			std::cout << std::endl;
			break;
		}

	}

	std::cout << "GAME OVER\n";
	system("pause");
	return 0;
}

