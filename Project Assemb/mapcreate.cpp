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



	//Determining where the bats, wumpus, pits, and player are
	std::vector<int> filler;
	for (int i = 0; i < 6; i++)
	{
		x = dis(gen);
		y = 0;
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
	map::player = filler[0];
	map::wumpus = filler[1];
	map::pit1 = filler[2];
	map::pit2 = filler[3];
	map::bats1 = filler[4];
	map::bats2 = filler[5];
}

int map::batmove()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 19);

	player = dis(gen);
	return 0;
}

void map::printplayer()
{
	std::cout << "You are in room: " << player << std::endl;
	std::cout << "Adjacent rooms are: " << layout.roomarray[player][0] << " ";
	std::cout << layout.roomarray[player][1] << " ";
	std::cout << layout.roomarray[player][2] << std::endl;
	std::cout << "You have " << arrowcount << " arrows left.\n";
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
	if (player == wumpus)
	{
		std::cout << "You lose as the Wumpus ate you";
		return 1;
	}
	if (player == pit1)
	{
		std::cout << "You lose as you fell in a pit";
		return 1;
	}
	if (player == pit2)
	{
		std::cout << "You lose as you fell in a pit";
		return 1;
	}
	if (player == bats1)
	{
		std::cout << "Bats carry you away to a random room!\n";
		batmove();
		if (dead() == 1)
		{
			return 1;
		}
	}
	if (player == bats2)
	{
		std::cout << "Bats carry you away to a random room!\n";
		batmove();
		if (dead() == 1)
		{
			return 1;
		}
	}
	return 0;
}

void map::detect()
{
	for (int i = 0; i < 3; i++)
	{
		if (layout.roomarray[player][i] == wumpus)
		{
			std::cout << "I smell a wumpus.\n";
		}
		if (layout.roomarray[player][i] == bats1)
		{
			std::cout << "I hear a bat.\n";
		}
		if (layout.roomarray[player][i] == bats2)
		{
			std::cout << "I hear a bat.\n";
		}
		if (layout.roomarray[player][i] == pit1)
		{
			std::cout << "I feel a breeze.\n";
		}
		if (layout.roomarray[player][i] == pit2)
		{
			std::cout << "I feel a breeze.\n";
		}
	}
}

void map::wumpmove()
{
	if (arrowcount < 5)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 3);

		int x = dis(gen);

		if (x < 3)
		{
			wumpus = layout.roomarray[wumpus][dis(gen)];
		}
	}
}


bool map::shoot()
{
	if (arrowcount > 0)
	{
		int x;
		int y = 0;
		std::string path;
		arrowcount--;
		std::cout << "Which path would you like to shoot (Example: 2-7-6): ";
		while (0 == 0)
		{
			std::cin.ignore();
			getline(std::cin, path);
			int x, y, z;
			char c;
			std::stringstream(path) >> x >> c >> y >> c >> z;

			if ((layout.roomarray[player][0] == x) || (layout.roomarray[player][1] == x) || (layout.roomarray[player][2] == x))
			{
				if ((layout.roomarray[x][0] == y) || (layout.roomarray[x][1] == y) || (layout.roomarray[x][2] == y))
				{
					if ((layout.roomarray[y][0] == z) || (layout.roomarray[y][1] == z) || (layout.roomarray[y][2] == z))
					{
						if ((wumpus == z) || (wumpus == y) || (wumpus == x))
						{
							return 1;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						std::cout << "Not a viable path, please enter a path: ";
					}
				}
				else
				{
					std::cout << "Not a viable path, please enter a path: ";
				}
			}
			else
			{
				std::cout << "Not a viable path, please enter a path: ";
			}

		}
	}
	else
	{
		std::cout << "Sorry you have no arrows";
	}
}