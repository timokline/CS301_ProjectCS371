#include <iostream>
#include <bitset>
#include <cstdint>
#include "roomfill.h"


using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 16;
using Stats = std::bitset<MAX_COMPONENTS>;

extern "C" Stats attack(Stats, Stats); // written in assembly!

void combat() {
	Stats weaponStats;
	weaponStats[1] = 1;

	Stats monsterStats;
	monsterStats[1] = 1;

	int multiplier = attack(monsterStats, weaponStats).count();

}
