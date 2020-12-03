#include "combat.h"

extern "C" int attack(unsigned int, unsigned int); // written in assembly!

void combat(double health) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 8);
	std::uniform_int_distribution<> dmg(3, 6);

	unsigned int crit1 = 0;
	unsigned int crit2 = 0;
	auto buff = dis(gen);
	

	std::cout << "The enemy has " << health << " health." << std::endl;
	while (health > 0.0)
	{
		auto totalDamage = 0;
		std::cout << "Hit Enter to attack" << std::endl;
		std::cin.ignore();

		//Crit Calculator 
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

		//std::cout << "crit1:" << crit1 << std::endl;
		//std::cout << "crit2:" << crit2 << std::endl;

		auto critVal = attack(crit1, crit2);//Stats(attack(monsterStats, weaponStats)).count();
		
		if (critVal > 1.0)
		{
			std::cout << "CRIT!\n";
			totalDamage = 2* dmg(gen);
		}
		else
			totalDamage =  dmg(gen);




		health -= totalDamage;
		std::cout << "You deal " << totalDamage << " damage." << std::endl;
		std::cout << "The enemy has " << health << " health left." << std::endl;

		crit1 = 0;
		crit2 = 0;
	}

}

