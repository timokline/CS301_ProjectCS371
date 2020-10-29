#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

using inventoryType = std::uint32_t;
const inventoryType MAX_INVENTORY = 10;

struct Player
{
	int room;
	int health;
	inventoryType inventory[MAX_INVENTORY];
};

#endif // !PLAYER_H