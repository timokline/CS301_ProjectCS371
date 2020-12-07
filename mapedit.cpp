#include "mapcreate.h"
#include "combat.h"

////////////////////////////////////////////////////////////
//			Player Movement Funtion
////////////////////////////////////////////////////////////
void map::moveplayer()
{
	int x = 0;
	std::string input;
	//std::cin.ignore();
	std::cout << "Which adjacent room would you like to go to? ";
	while (std::getline(std::cin, input))
	{
		std::istringstream instream(input);
		instream >> x;
		if (!instream)
		{
			std::cout << "Please enter a number." << std::endl;
			continue;
		}

		if (x == layout.roomarray[player.room][0] || x == layout.roomarray[player.room][1] || x == layout.roomarray[player.room][2])
		{
			player.room = x;
			break;
		}
		else
		{
			std::cout << "Not a viable answer. Please answer one of the rooms listed above. " << std::endl;
		}
	}
}

////////////////////////////////////////////////////////////
//			Determining Encounter Funtion
////////////////////////////////////////////////////////////
int map::question(Player& player)
{
	//RNG 
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> SKELETON_HEALTH(20, 26);
	std::uniform_int_distribution<> OOZE_HEALTH(17, 22);
	std::uniform_int_distribution<> BOSS_HEALTH(50, 60);
	std::uniform_int_distribution<> MIMIC_HEALTH(5, 6);
	std::uniform_int_distribution<> ELEMENT(0, 3);
	
	//Unique floor enemies
	std::string mod1, mod2;
	switch (player.difficulty)
	{
	case 0:
		mod1 = "";
		mod2 = "";
		break;
	case 1:
		mod1 = "Frog ";
		mod2 = "Snail ";
		break;
	default:
		break;
	}

	//Skeleton Encounter
	if (map::player.room == map::s.room1 || map::player.room == map::s.room2 || map::player.room == map::s.room3 || map::player.room == map::s.room4)
	{
		map::s.type |= (1 << ELEMENT(gen));
		std::cout << "\nA ";
		switch (map::s.type)
		{
		case 1<<0: //0b0001
			std::cout << "Fire ";
			break;
		case 1<<1: //0b0010
			std::cout << "Water ";
			break;
		case 1<<2: //0b0100
			std::cout << "Mossy ";
			break;
		default:   //0b1000
			break;
		}
		std::cout << "Skeleton "<< mod1 << "appears!\n";
		player.playerhp = playercombat(SKELETON_HEALTH(gen) + (5 * player.difficulty), map::s, player);
		if (player.playerhp == 0)
			return 0;
		std::cout << "\nThe Skeleton " << mod1 << "'s bones fall to the ground.\n";
		map::s.type = 0<<0;
		remove(map::player.room);
	}

	//Ooze Encounter
	else if (map::player.room == map::o.room1 || map::player.room == map::o.room2 || map::player.room == map::o.room3 || map::player.room == map::o.room4)
	{
		map::o.type |= (1 << ELEMENT(gen));
		std::cout << "\nA";
		switch (map::o.type)
		{
		case 1<<0:	//0b0001
			std::cout << " Fire ";
			break;
		case 1<<1:	//0b0010
			std::cout << " Water ";
			break;
		case 1<<2:	//0b0100
			std::cout << " Mossy ";
			break;
		default:	//0b1000
			std::cout << "n ";
			break;
		}
		std::cout << "Ooze " << mod2 << "appears!\n";
		player.playerhp = playercombat(OOZE_HEALTH(gen) + (5 * player.difficulty), map::o, player);
		if (player.playerhp == 0)
			return 0;
		std::cout << "\nThe Ooze " << mod2 << " drips away.\n";
		map::o.type = 0<<0;
		remove(map::player.room);
	}

	//Boss Encounter
	else if (map::player.room == map::bigboss.room1)
	{
		if (player.key == 1)
		{
			std::cout << "You open the door with your key!\n";
			std::cout << "\nA big enemy blocks your exit!\n";
			if (player.difficulty == 1)
			{
				player.playerhp = finalbosscombat(map::bigboss, player);
			}
			else
			{
				player.playerhp = playercombat(BOSS_HEALTH(gen) + (5 * player.difficulty), map::bigboss, player);
			}
			if (player.playerhp == 0)
				return 0;
			
			remove(map::player.room);
		}
		else
		{
			std::cout << "You need a key to enter!\n";
		}

		
	}

	//Chest & Mimic encounter
	else if (map::player.room == map::m.room1 || map::player.room == map::m.room2 || map::player.room == map::c.room1 || map::player.room == map::c.room2 || map::player.room == map::c.room3 || map::player.room == map::c.room4)
	{
		std::string input;
		std::cout << "There is a chest would you like to open it? ";
		while (std::getline(std::cin, input))
		{
			std::istringstream instream(input);
			instream >> input;
			if (!instream)
			{
				std::cout << "Please enter Yes or No. " << std::endl;
				continue;
			}
			std::transform(input.begin(), input.end(), input.begin(),
				[](unsigned char c) { return std::tolower(c); });
			if (input == "yes")
			{
				player.playerhp = openchest(MIMIC_HEALTH(gen), player); 
				remove(map::player.room);
				break;
			}
			else if (input == "no")
			{
				std::cout << "You walk away...\n";
				break;
			}
			else
			{
				std::cout << "Not a viable answer. Please answer Yes or No." << std::endl;
			}
		}
	}

	//Empty Room Encounter
	else
	{
		std::cout << "\nNothing here...\n";
	}
	std::cout << "\n--------------------------------\n";
	return player.playerhp;
}

////////////////////////////////////////////////////////////
//			Chest/Mimic Encounter Function
////////////////////////////////////////////////////////////
int map::openchest(int x, Player& player)
{
	//Chests
	if (map::player.room == map::c.room1)
	{
		if (player.fire)
			std::cout << "Your Fire Sword burns brighter.\n";
		else
			std::cout << "You found a Fire Sword.\n";
		player.fire += 1;
	}
	else if (map::player.room == map::c.room2)
	{
		if (player.grass)
			std::cout << "Your Wooden Spear hardens.\n";
		else
			std::cout << "You found a Wooden Spear.\n";
		player.grass += 1;
	}
	else if (map::player.room == map::c.room3)
	{
		if (player.water)
			std::cout << "Your Water Axe grows stronger.\n";
		else
			std::cout << "You found a Water Axe.\n";
		player.water += 1;
	}
	else if (map::player.room == map::c.room4)
	{
		std::cout << "You found a key, I wonder what this is for...\n";
		player.key = 1;
	}

	//Mimics
	if (map::player.room == map::m.room1 || map::player.room == map::m.room2)
	{
		std::cout << "Seems empty...\n" << "JUST KIDDING IT WAS A WOODEN MIMIC\n";
		player.playerhp = playercombat(x + (5 * player.difficulty), map::m, player);
		if (player.playerhp == 0)
			return 0;
		std::cout << "\nThe Mimic splinters apart.\n";
	}
	return player.playerhp;
}

////////////////////////////////////////////////////////////
//			Room Clearing Funtion 
////////////////////////////////////////////////////////////
void map::remove(int x)
{
	if (x == map::s.room1)
	{
		map::s.room1 = 100;
	}
	else if (x == map::s.room2)
	{
		map::s.room2 = 100;
	}
	else if (x == map::s.room3)
	{
		map::s.room3 = 100;
	}
	else if (x == map::s.room4)
	{
		map::s.room4 = 100;
	}
	else if (x == map::o.room1)
	{
		map::o.room1 = 100;
	}
	else if (x == map::o.room2)
	{
		map::o.room2 = 100;
	}
	else if (x == map::o.room3)
	{
		map::o.room3 = 100;
	}
	else if (x == map::o.room4)
	{
		map::o.room4 = 100;
	}
	else if (x == map::m.room1)
	{
		map::m.room1 = 100;
	}
	else if (x == map::m.room2)
	{
		map::m.room2 = 100;
	}
	else if (x == map::c.room1)
	{
		map::c.room1 = 100;
	}
	else if (x == map::c.room2)
	{
		map::c.room2 = 100;
	}
	else if (x == map::c.room3)
	{
		map::c.room3 = 100;
	}
	else if (x == map::c.room4)
	{
		map::c.room4 = 100;
	}
	else if (x == map::bigboss.room1)
	{
		map::bigboss.room1 = 100;
	}
}

////////////////////////////////////////////////////////////
//			Determining if Floor Boss is alive function
////////////////////////////////////////////////////////////
bool map::bossdead()
{
	if (map::bigboss.room1 == 100)
	{
		return 1;
	}
	return 0;
}