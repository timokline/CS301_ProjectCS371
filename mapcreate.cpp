#include "mapcreate.h"
#include <string>
#include <sstream>

map::map()
{
	//creating everything and running test outputs
	fillrooms();
}

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

	std::vector<int> filler;
	for (int i = 0; i < 10; i++)
	{
		x = dis(gen);
		y = 0;
		for (auto j : filler)
		{
			if (x == 0)
			{
				y++;
			}
			if (x == 19)
			{
				y++;
			}
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

	map::s1.room = filler[0];
	map::s2.room = filler[1];
	map::s3.room = filler[2];
	map::s4.room = filler[3];
	map::o1.room = filler[4];
	map::o2.room = filler[5];
	map::o3.room = filler[6];
	map::o4.room = filler[7];
	map::c1.room = filler[8];
	map::c2.room = filler[9];
	map::bigboss.room = 19;
	map::player.room = 0;
}

void map::printplayer()
{
	std::cout << "You are in room: " << player.room << std::endl;
	std::cout << "Adjacent rooms are: ";
	std::cout<< layout.roomarray[player.room][0] << " ";
	std::cout << layout.roomarray[player.room][1] << " ";
	std::cout << layout.roomarray[player.room][2] << std::endl;
}

void map::moveplayer()
{
	int x = 0;
	std::string input;
	std::cout << "Which adjacent room would you like to go to? ";
	while (0 == 0)
	{
		std::getline(std::cin, input);
		std::istringstream instream(input);
		instream >> x;
		if (!instream)
		{
			std::cout << "Please enter a number." << std::endl;
			continue;
		}

		if (x == layout.roomarray[player.room][0] || x == layout.roomarray[player.room][1] || x == layout.roomarray[player.room][2])
		{
			player.room = x;
			break;
		}
		else
		{
			std::cout << "Not a viable answer. Please answer one of the rooms listed above." << std::endl;
		}
	}
}

bool map::question()
{
	if (map::player.room == map::s1.room || map::player.room == map::s2.room || map::player.room == map::s3.room || map::player.room == map::s4.room)
	{
		std::cout << "\nSkeleton\n";
	}
	else if (map::player.room == map::o1.room || map::player.room == map::o2.room || map::player.room == map::o3.room || map::player.room == map::o4.room)
	{
		std::cout << "\nOoze\n";
	}
	else if (map::player.room == map::bigboss.room)
	{
		std::cout << "\nBoss\n";
		return true;
	}
	else if (map::player.room == map::c1.room)
	{
		std::cout << "\nTreasure\n";
	}
	else
	{
		std::cout << "\nNada\n";
	}
	return false;
}




