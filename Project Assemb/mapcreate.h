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
	void detect();
	void wumpmove();
	bool shoot();
private:
	void fillrooms();
	int batmove();
	room layout;
	int player;
	int wumpus;
	int bats1;
	int bats2;
	int pit1;
	int pit2;
	int arrowcount = 5;
};

#endif