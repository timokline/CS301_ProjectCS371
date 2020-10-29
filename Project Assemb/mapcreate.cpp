#include "mapcreate.h"

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

	map::player = 0;
}

void map::printplayer()
{
	std::cout << "You are in room: " << player << std::endl;
	std::cout << "Adjacent rooms are: ";
	std::cout<< layout.roomarray[player][0] << " ";
	std::cout << layout.roomarray[player][1] << " ";
	std::cout << layout.roomarray[player][2] << std::endl;
}

void map::moveplayer()
{
	int x = 0;
	std::cout << "Which adjacent room would you like to go to? ";
	while (0 == 0)
	{
		std::cin >> x;
		if (x == layout.roomarray[player][0])
		{
			player = x;
			break;
		}
		if (x == layout.roomarray[player][1])
		{
			player = x;
			break;
		}
		if (x == layout.roomarray[player][2])
		{
			player = x;
			break;
		}
		std::cout << "Not a viable answer. Please answer on of the rooms listed above." << std::endl;
	}
}

bool map::dead()
{
	return 0;
}




