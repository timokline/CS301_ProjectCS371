#define MAPCREATE_H
#ifdef MAPCREATE_H

#include <random>
#include <iostream>
#include <string>
#include <sstream>

struct room
{
	int roomarray[20][3];
};

class map
{
public:
	map();
	void printplayer();
	void moveplayer();
	bool dead();
private:
	void fillrooms();
	room layout;
	int player;
};

#endif