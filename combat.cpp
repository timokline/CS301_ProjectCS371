#include <iostream>
#include <bitset>
#include <cstdint>
#include <random>
#include "roomfill.h"


using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 8;
using Stats = std::bitset<MAX_COMPONENTS>;

extern "C" Stats attack(Stats, Stats); // written in assembly!

void combat() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 7);

	Stats weaponStats;
	weaponStats[1] = 1;

	Stats monsterStats;
	monsterStats[1] = 1;

	int multiplier = attack(monsterStats, weaponStats).count();

}
