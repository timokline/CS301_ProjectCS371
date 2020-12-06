#ifndef COMBAT_H
#define COMBAT_H

#include "main.h"
#include "characters.h"

int playercombat(int health, object enemy, Player& player);
int typeAdv(Player& player, int totalDamage, object& enemy);
int enemycombat(object& enemy, Player player);
int finalbosscombat(object enemy, Player& player);
int finalbosscombat2(object& enemy, Player player, int& health);


#endif // !COMBAT_H

