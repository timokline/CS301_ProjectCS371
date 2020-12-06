#include "mapcreate.h"
#include "combat.h"

////////////////////////////////////////////////////////////
//			Map Class Destructor 
////////////////////////////////////////////////////////////
map::~map()
{}

////////////////////////////////////////////////////////////
//			Map Class Constructor 
////////////////////////////////////////////////////////////
map::map(Player& temp)
{
	//creating everything and running test outputs
	fillrooms();
	player.playerhp = temp.playerhp;
	player.potions = temp.potions;
}

////////////////////////////////////////////////////////////
//			Creating/Filling the Rooms of map 
////////////////////////////////////////////////////////////
void map::fillrooms()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 19);


	//Linking the rooms together
	int x;
	int y;
	std::vector<int> roomnums;
	for (int i = 0; i < 20; i++)
	{
		x = dis(gen);
		y = 0;
		for (auto j : roomnums)
		{
			if (x == j)
			{
				y++;
			}
		}
		if (y > 0)
		{
			i--;
		}
		else
		{
			roomnums.push_back(x);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		roomnums.push_back(roomnums[i]);
	}


	//Creating the rooms
	for (int i = 0; i < 20; i++)
	{
		if (i == 0)
		{
			layout.roomarray[roomnums[i]][0] = roomnums[19];
			layout.roomarray[roomnums[i]][1] = roomnums[1];
			layout.roomarray[roomnums[i]][2] = roomnums[10];
		}
		else if (i == 19)
		{
			layout.roomarray[roomnums[i]][0] = roomnums[18];
			layout.roomarray[roomnums[i]][1] = roomnums[0];
			layout.roomarray[roomnums[i]][2] = roomnums[9];
		}
		else
		{
			layout.roomarray[roomnums[i]][0] = roomnums[i - 1];
			layout.roomarray[roomnums[i]][1] = roomnums[i + 1];
			layout.roomarray[roomnums[i]][2] = roomnums[i + 10];
		}
	}

	//filler
	for (int i = 0; i < 14; i++)
	{
		x = dis(gen);
		y = 0;
		if (x == 0)
		{
			y++;
		}
		if (x == 19)
		{
			y++;
		}
		for (auto j : filler)
		{
			if (x == j)
			{
				y++;
			}
		}
		if (y > 0)
		{
			i--;
		}
		else
		{
			filler.push_back(x);
		}
	}
	
	//Filling rooms with objects with stats
	map::s.room1 = filler[0];
	map::s.room2 = filler[1];
	map::s.room3 = filler[2];
	map::s.room4 = filler[3];
	map::s.type = 0<<0;
	map::s.high = 7;
	map::s.low = 3;

	map::o.room1 = filler[4];
	map::o.room2 = filler[5];
	map::o.room3 = filler[6];
	map::o.room4 = filler[7];
	map::o.type = 0<<0; 
	map::o.high = 6;
	map::o.low = 5;

	map::m.room1 = filler[8];
	map::m.room2 = filler[9];
	map::m.type = 1<<2; 
	map::m.high = 13;
	map::m.low = 10;

	map::c.room1 = filler[10];
	map::c.room2 = filler[11];
	map::c.room3 = filler[12];
	map::c.room4 = filler[13];

	map::bigboss.room1 = 19;
	map::bigboss.high = 6;
	map::bigboss.low = 5;

	map::player.room = 0;
	
	//Cheating to see what rooms have what
	/*
	std::cout << map::s.room1 << std::endl;
	std::cout << map::s.room2 << std::endl;
	std::cout << map::s.room3 << std::endl;
	std::cout << map::s.room4 << std::endl;
	std::cout << map::o.room1 << std::endl;
	std::cout << map::o.room2 << std::endl;
	std::cout << map::o.room3 << std::endl;
	std::cout << map::o.room4 << std::endl;
	std::cout << map::m.room1 << std::endl;
	std::cout << map::m.room2 << std::endl;
	std::cout << map::c.room1 << std::endl;
	std::cout << map::c.room2 << std::endl;
	std::cout << map::c.room3 << std::endl;
	std::cout << map::c.room4 << std::endl;
	std::cout << map::player.room << std::endl;
	std::cout << map::bigboss.room1 << std::endl;
	*/


}


////////////////////////////////////////////////////////////
//			Printing Player Location
////////////////////////////////////////////////////////////
void map::printplayer()
{
	std::cout << "You are in room: " << player.room << std::endl;
	std::cout << "Adjacent rooms are: ";
	std::cout << layout.roomarray[player.room][0] << " ";
	std::cout << layout.roomarray[player.room][1] << " ";
	std::cout << layout.roomarray[player.room][2] << std::endl;
}