#include "combat.h"

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 8;
using Stats = std::bitset<MAX_COMPONENTS>;
const int MAX_SELECTIONS = 5;

extern "C" int attack(Stats, Stats); // written in assembly!

void combat(double health) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 8);
	std::uniform_int_distribution<> dmg(3, 6);

	Stats weaponStats;
	Stats monsterStats;

	auto affinity = dis(gen);
	auto attribute = dis(gen);
	for (int selection = 0; selection < 5; selection++)
	{
		monsterStats[attribute] = 1.0;
		weaponStats[affinity] = 1.0;
	}

	/*prints the bits that have been set to true.*/
	//std::cout << monsterStats << std::endl;
	//std::cout << weaponStats << std::endl;
	std::cout << "The enemy has " << health << " health." << std::endl;
	while (health > 0.0)
	{
		std::cout << "Hit Enter to attack" << std::endl;
		std::cin.ignore();
		auto multiplier = attack(monsterStats, weaponStats);//Stats(attack(monsterStats, weaponStats)).count();
		if (multiplier > 1.0)
		{
			std::cout << "CRIT!\n";
			multiplier *= (float)dmg(gen);
		}
		else
			multiplier = (float) dmg(gen);

		health -= multiplier;
		std::cout << "You deal " << multiplier << " damage." << std::endl;
		std::cout << "The enemy has " << health << " health left." << std::endl;
	}

}