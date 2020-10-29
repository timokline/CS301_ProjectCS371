#define MAPCREATE_H
#ifdef MAPCREATE_H

#include <random>
#include <iostream>
#include <string>
#include <sstream>
#include "roomfill.h"

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
	void question();
private:
	void fillrooms();
	room layout;
	int player;
	skeleton s1;
	skeleton s2;
	skeleton s3;
	skeleton s4;
	ooze o1;
	ooze o2;
	ooze o3;
	ooze o4;
	boss bigboss;
};

#endif