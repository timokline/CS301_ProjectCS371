#include <iostream>
#include <bitset>
#include <cstdint>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 32;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 16;
using Signature = std::bitset<MAX_COMPONENTS>;

extern "C" int bar(Signature, Signature); // written in assembly!

int combat() {
	Signature monsterProp;
	Signature weaponProp;
	monsterProp[1] = 1;
	weaponProp[1] = 1;
	std::cout << "Bar returns " << bar(monsterProp, weaponProp) << "\n";
	system("pause");
	return 0;
}
