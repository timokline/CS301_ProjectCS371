#include "combat.h"

extern "C" int critCalc(unsigned int, unsigned int); // written in assembly!
extern "C" int typeCalc(unsigned int, unsigned int); // written in assembly!

void combat(double health, int attributeM) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 8);
	std::uniform_int_distribution<> dmg(4,6);

	unsigned int crit1 = 0;
	unsigned int crit2 = 0;
	auto buff = dis(gen);
	auto totalDamage = 0;
	int type;
	std::string input;
	int attributeW;

	std::cout << "The enemy has " << health << " health.\n";

	while (health > 0.0)
	{
		////////////////////////////////////////////////////////////
		//Type Calculator
		////////////////////////////////////////////////////////////
		std::cout << "Hit ENTER to choose weapon.\n";
		while (std::getline(std::cin, input))
		{
			std::istringstream instream(input);
			instream >> type;
			if (!instream)
			{
				std::cout << "Would you like to attack with:\n";
				std::cout << " ---------------------------------------------------------- " << std::endl;
				std::cout << "(                   )                (                     )" << std::endl;
				std::cout << " ) A Fire Sword(1) (  A Water Axe(2)  ) A Wooden Spear(3) ( " << std::endl;
				std::cout << "(                   )                (                     )" << std::endl;
				std::cout << " ---------------------------------------------------------- " << std::endl;
				continue;
			}
			
			if (type == 1)
			{
				attributeW = 1;
				break;
			}
			else if (type == 2)
			{
				attributeW = 0;
				break;
			}
			else if (type == 3)
			{
				attributeW = -1;
				break;
			}
			else
			{
				std::cout << "Not a viable answer. Please answer one of the weapons listed above." << std::endl;
			}
		}

		std::cout << "\n";

		totalDamage = dmg(gen);

		auto weakness = typeCalc(attributeW, attributeM); // Calls assembly function to calculate type advantage
		if (weakness == 2 || weakness == -1)
		{
			std::cout << "SUPER EFFECTIVE!\n";
			totalDamage = 2 * totalDamage;
		}
		else if (weakness == -2 || weakness == 1)
		{
			std::cout << "Not Very Effective.\n";
			totalDamage = totalDamage / 2;

		}



		////////////////////////////////////////////////////////////
		//Crit Calculator 
		////////////////////////////////////////////////////////////
		buff = dis(gen);
		for (int counter = 0; counter < 6; counter++)
		{
			crit1 |= (1 << buff);
		}
		buff = dis(gen);
		for (int counter = 0; counter < 6; counter++)
		{
			crit2 |= (1 << buff);
		}

		auto critVal = critCalc(crit1, crit2);  // Calls assembly function to calculate crits
		
		if (critVal > 1.0)
		{
			std::cout << "CRIT!\n";
			totalDamage = 2 * totalDamage;
		}


		health -= totalDamage;
		std::cout << "You deal " << totalDamage << " damage.\n";
		
		if (health > 0.0)
		{
			std::cout << "The enemy has " << health << " health left.\n\n";
		}
		else
		{
			std::cout << "The enemy has 0 health left.\n\n";
		}

		crit1 = 0;
		crit2 = 0;
		totalDamage = 0;
	}

}
