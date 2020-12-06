#include "combat.h"

extern "C" int critCalc(unsigned int, unsigned int); // written in assembly!
extern "C" int typeCalc(unsigned int, unsigned int); // written in assembly!

////////////////////////////////////////////////////////////
//			Combat Loop
////////////////////////////////////////////////////////////
int playercombat(int health, object enemy, Player& player) 
{
	//RNG
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9);
	std::uniform_int_distribution<> dmg(0,2);

	unsigned int crit1 = 0<<0;
	unsigned int crit2 = 0<<0;
	auto buff = dis(gen);
	int totalDamage;
	enemy.block = 0;
	enemy.strength = 0;
	
	std::cout << "The enemy has " << health << " health.\n";

	//Main Combat Loop
	while (health > 0)
	{
		std::cout << "\n--------------------------------\n";
		totalDamage = dmg(gen);

		totalDamage = typeAdv(player, totalDamage, enemy);

		if (player.block == 1)
		{
			std::cout << "You block the enemies action.\n";
			enemy.strength = 0;
		}
		else
		{
			//Crit Calculator 
			for (int counter = 0; counter < 6; counter++)
			{
				buff = dis(gen);
				crit1 |= (1 << buff);
				//std::cout << crit1 << std::endl;
				buff = dis(gen);
				crit2 |= (1 << buff);
				//std::cout << crit2 << std::endl;
			}

			auto critVal = critCalc(crit1, crit2);  // Calls assembly function to calculate crits

			//Count Set Bits
			unsigned int multiplier = 0;
			while (critVal) {
				critVal &= (critVal - 1 << 0);
				multiplier++;
			}

			if (multiplier > 2.0)
			{
				std::cout << "CRIT!\n";
				totalDamage = 2 * totalDamage;
			}

			//Remaining Health Calculator and text
			if (enemy.block == 1)
			{
				std::cout << "The enemy blocks your attack.\n";
				enemy.block = 0;
			}
			else
			{
				health -= totalDamage;
				std::cout << "You deal " << totalDamage << " damage.\n";
			}

			if (health > 0)
			{
				std::cout << "The enemy has " << health << " health left.\n\n";
			}
			else
			{
				std::cout << "The enemy has 0 health left.\n\n";
				break;
			}

			player.playerhp = enemycombat(enemy, player);
		}

		crit1 = 0;
		crit2 = 0;
		totalDamage = 0;
		player.block = 0;
		if (player.blockcd)
		{
			player.blockcd = player.blockcd - 1;
		}

		if (player.playerhp <= 0)
		{
			return player.playerhp;
		}
	}
	
	return player.playerhp;
}

////////////////////////////////////////////////////////////
//			Enemy Combat Funtion
////////////////////////////////////////////////////////////
int enemycombat(object& enemy, Player player)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dmg(enemy.low, enemy.high);
	std::uniform_int_distribution<> action(0, 4);
	int temp = dmg(gen) + (5 * player.difficulty);
	int decide = action(gen);
	std::cout << "You have " << player.playerhp << " health.\n";

	if (enemy.strength == 1)
	{
		enemy.strength = 0;
		temp = temp * 2;
		std::cout << "You are hit for " << temp << ".\n";
		player.playerhp = player.playerhp - temp;
	}
	else if (decide == 0 || decide == 1 || decide == 2)
	{
		std::cout << "You are hit for " << temp << ".\n";
		player.playerhp = player.playerhp - temp;
	}
	else if (decide == 3)
	{
		std::cout << "The enemy is on gaurd.\n";
		enemy.block = 1;
	}
	else
	{
		std::cout << "The enemy is charging up!\n";
		enemy.strength = 1;
	}	
	
	//Checking if you are dead
	if (player.playerhp == 0)
	{
		std::cout << "You have 0 health left.\n";
		return 0;
	}
	
	std::cout << "You have " << player.playerhp << " health and " << player.potions << " potions left.\n";
	return player.playerhp;
}

////////////////////////////////////////////////////////////
//			Final Boss Combat Loop
////////////////////////////////////////////////////////////
int finalbosscombat(object enemy, Player& player)
{
	//RNG
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9);
	std::uniform_int_distribution<> dmg(0, 2);

	unsigned int crit1 = 0 << 0;
	unsigned int crit2 = 0 << 0;
	auto buff = dis(gen);
	int totalDamage;
	enemy.block = 0;
	enemy.strength = 0;
	int health = 100;

	std::cout << "The enemy has " << health << " health.\n";

	//Main Combat Loop
	while (health > 0)
	{
		std::cout << "\n--------------------------------\n";
		totalDamage = dmg(gen);

		totalDamage = typeAdv(player, totalDamage, enemy);

		if (player.block == 1)
		{
			std::cout << "You block the enemies action.\n";
			enemy.strength = 0;
		}
		else
		{
			//Crit Calculator 
			for (int counter = 0; counter < 6; counter++)
			{
				buff = dis(gen);
				crit1 |= (1 << buff);
				//std::cout << crit1 << std::endl;
				buff = dis(gen);
				crit2 |= (1 << buff);
				//std::cout << crit2 << std::endl;
			}

			auto critVal = critCalc(crit1, crit2);  // Calls assembly function to calculate crits

			//Count Set Bits
			unsigned int multiplier = 0;
			while (critVal) {
				critVal &= (critVal - 1 << 0);
				multiplier++;
			}

			if (multiplier > 2.0)
			{
				std::cout << "CRIT!\n";
				totalDamage = 2 * totalDamage;
			}

			//Remaining Health Calculator and text
			if (enemy.block == 1)
			{
				std::cout << "The enemy blocks your attack.\n";
				enemy.block = 0;
			}
			else
			{
				health -= totalDamage;
				std::cout << "You deal " << totalDamage << " damage.\n";
			}

			if (health > 0)
			{
				std::cout << "The enemy has " << health << " health left.\n\n";
			}
			else
			{
				std::cout << "The enemy has 0 health left.\n\n";
				break;
			}

			//Changes enemy type each turn after below 50% hp
			if (health < 50)
			{
				enemy.type = 1 << dmg(gen);
				switch (enemy.type)
				{
				case 1 << 0:
					std::cout << "The boss has become firey.\n";
					break;
				case 1 << 1:
					std::cout << "The boss has become watery.\n";
					break;
				case 1 << 2:
					std::cout << "The boss has become mossy.\n";
					break;
				default:
					break;
				}
			}
			player.playerhp = finalbosscombat2(enemy, player, health);
		}

		crit1 = 0;
		crit2 = 0;
		totalDamage = 0;
		player.block = 0;

		if (player.playerhp <= 0)
		{
			return player.playerhp;
		}
	}

	return player.playerhp;
}

////////////////////////////////////////////////////////////
//			Final Boss Combat Funtion
////////////////////////////////////////////////////////////
int finalbosscombat2(object& enemy, Player player, int& health)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dmg(enemy.low, enemy.high);
	std::uniform_int_distribution<> action(0, 4);
	int temp = dmg(gen) + (5 * player.difficulty);
	int decide = action(gen);
	std::cout << "You have " << player.playerhp << " health.\n";
	
	//Above 50% hp
	if (health > 50)
	{
		if (enemy.strength == 1)
		{
			enemy.strength = 0;
			temp = temp * 2;
			std::cout << "You are hit for " << temp << ".\n";
			player.playerhp = player.playerhp - temp;
		}
		else if (decide == 0 || decide == 1 || decide == 2)
		{
			std::cout << "You are hit for " << temp << ".\n";
			player.playerhp = player.playerhp - temp;
		}
		else if (decide == 3)
		{
			std::cout << "The enemy is on gaurd.\n";
			enemy.block = 1;
		}
		else
		{
			std::cout << "The enemy is charging up!\n";
			enemy.strength = 1;
		}
	}
	//Below 50% hp
	else
	{
		//Fire
		if (enemy.type == 1 << 0)
		{
			if (decide == 0 || decide == 1 || decide == 2)
			{
				temp = temp * 1.5;
				std::cout << "You are hit for " << temp << ".\n";
				player.playerhp = player.playerhp - temp;
			}
			else
			{
				temp = temp * 0.5;
				std::cout << "You are hit for " << temp << ".\n";
				player.playerhp = player.playerhp - temp ;
				int temp = dmg(gen) + (5 * player.difficulty);
				std::cout << "You are hit for " << temp << ".\n";
				player.playerhp = player.playerhp - temp;
			}
		}
		//Water
		else if (enemy.type == 1 << 1)
		{
			if (decide == 0 || decide == 1 || decide == 2)
			{
				std::cout << "The enemy is on gaurd.\n";
				enemy.block = 1;
			}
			else
			{
				std::cout << "You are hit for " << temp << ".\n";
				player.playerhp = player.playerhp - temp;
			}
		}
		//Moss
		else if (enemy.type == 1 << 2)
		{
			temp = temp * 0.75;
			std::cout << "You are hit for " << temp  << ".\n";
			player.playerhp = player.playerhp - temp;
			std::cout << "The boss heals for " << temp << ".\n";
			if (health + temp > 50)
			{
				health = 50;
			}
			else
				health = health + temp ;
			std::cout << "The enemy has " << health << " health left.\n\n";
		}
	}


	//Checking if you are dead
	if (player.playerhp == 0)
	{
		std::cout << "You have 0 health left.\n";
		return 0;
	}

	std::cout << "You have " << player.playerhp << " health and " << player.potions << " potions left.\n";
	return player.playerhp;
}

////////////////////////////////////////////////////////////
//			Type Advantage Clac
////////////////////////////////////////////////////////////
/*
Allows you to pick a weapon that you have or your fist if you want 
to attack at calculates damage based on if you are super effective
or not 
*/
int typeAdv(Player& player, int totalDamage, object& enemy)
{
	int type;
	std::string input;
	unsigned int attributeW = 1<<3; //0x1000

	//Choosing Weapon
	std::cout << "Hit ENTER to choose weapon.\n";
	while (std::getline(std::cin, input))
	{
		std::istringstream instream(input);
		instream >> type;
		if (!instream)
		{
			std::cout << "(0) Fist\n(1) Potion\n";
			if (player.blockcd == 0)
				std::cout << "(2) Block\n";
			else
				std::cout << "Block cooldown:" << player.blockcd << std::endl;
			if (player.fire)
				std::cout << "(3) Fire Sword\n";
			if (player.water)
				std::cout << "(4) Water Axe\n";
			if (player.grass)
				std::cout << "(5) Wooden Spear\n";

			std::cout << "Which weapon would you like to attack with: ";
			continue;
		}

		if (type == 0)
		{
			std::cout << "\n";
			return totalDamage + 3;
		}
		else if (type == 1)
		{
			player.potions = player.potions - 1;
			player.playerhp += 50;
			std::cout << "\n";
			return 0;
		}
		else if (type == 2)
		{
			if (player.blockcd == 0)
			{
				player.block = 1;
				player.blockcd = 3;
				return 0;
			}
			else
			{
				std::cout << "Block cooldown:" << player.blockcd << std::endl;
			}
		}
		else if (type == 3 && player.fire)
		{
			attributeW |= (1 << 2);
			totalDamage = totalDamage + player.fire * 5; 
			break;
		}
		else if (type == 4 && player.water)
		{
			attributeW |= (1 << 0);
			totalDamage = totalDamage + player.water * 5;
			break;
		}
		else if (type == 5 && player.grass)
		{
			attributeW |= (1 << 1);
			totalDamage = totalDamage + player.grass * 5;
			break;
		}
		else
		{
			std::cout << "Not a viable answer. "
				<< "Please answer one of the weapons listed above. " << std::endl;
		}
		
	}
	std::cout << "\n";

	auto effectiveness = typeCalc(attributeW, enemy.type); // Calls assembly function to calculate type advantage
	if (effectiveness > 0)
		std::cout << "SUPER EFFECTIVE!\n";
	else if (effectiveness < 0)
		std::cout << "Not Very Effective.\n";
	return totalDamage + effectiveness;
}