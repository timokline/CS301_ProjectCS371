#ifndef MAPCREATE_H
#define MAPCREATE_H

#include<vector>

#include "main.h"
#include "characters.h"

enum class GameStates { PLAYING, EXIT };

struct room
{
	int roomarray[20][3];
};

class map
{
public:
	map(Player& player);
	~map();
	void printplayer();
	void moveplayer();
	int question(Player& player);
	int openchest(int x, Player& player);
	void remove(int x);
	bool bossdead();
private:
	void fillrooms();
	room layout;
	Player player;
	object s;
	object o;
	object m;
	object c;
	object bigboss;
public:
	std::vector<int> filler;
};


#endif