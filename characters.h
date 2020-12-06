#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
	int room;
	bool key = 0;
	int fire = 0;
	int water = 0;
	int grass = 0;
	int playerhp;
	int potions;
	int difficulty;
	bool block;
	int blockcd;
};

struct object
{
	int room1;
	int room2;
	int room3;
	int room4;
	int low;
	int high;
	unsigned int type;
	bool block;
	bool strength;
};


#endif // !PLAYER_H