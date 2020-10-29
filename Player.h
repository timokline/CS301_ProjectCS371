#pragma once
#include <cstdint>

using inventoryType = std::uint32_t;
const inventoryType MAX_INVENTORY = 10;

struct Player
{
	int room;
	int health;
	inventoryType inventory[MAX_INVENTORY];
};