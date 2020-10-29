#define MAPCREATE_H
#ifdef MAPCREATE_H

#include <random>
#include <iostream>
#include <string>

#include "roomfill.h"
#include "Player.h"

enum class GameStates { PLAYING, EXIT };

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
	bool question();
private:
	void fillrooms();
	room layout;
	Player player;
	skeleton s1;
	skeleton s2;
	skeleton s3;
	skeleton s4;
	ooze o1;
	ooze o2;
	ooze o3;
	ooze o4;
	chest c1;
	chest c2;
	boss bigboss;
};

#endif