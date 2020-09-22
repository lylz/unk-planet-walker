#include "Level.h"
#include "../utils/Randomizer.h"

Level::Level(unsigned int size)
{
	map_.resize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		map_[i].resize(size);

		for (unsigned int j = 0; j < size; j++)
		{
			map_[i][j] = (MapEntry::EMPTY);
		}
	}

	SetupWalls();
	SetupObstacles();
	SetupPassages();
	SetupEnemies();
	SetupConsumables();
}

void Level::SetupWalls()
{
	for (unsigned int i = 0; i < map_.size(); i++)
	{
		for (unsigned int j = 0; j < map_.size(); j++)
		{
			if (i == 0 || i == map_.size() - 1 || j == 0 || j == map_.size() - 1)
			{
				map_[i][j] = MapEntry::WALL;
			}
		}
	}
}

std::vector<std::vector<MapEntry>> Level::map()
{
	return map_;
}

void Level::SetupObstacles()
{
	PlaceObject(MapEntry::OBSTACLE, 5);
}

bool Level::HasNeighbors(int i, int j)
{
	return map_[i - 1][j] != MapEntry::EMPTY ||
		map_[i + 1][j] != MapEntry::EMPTY ||
		map_[i][j - 1] != MapEntry::EMPTY || 
		map_[i][j + 1] != MapEntry::EMPTY;
}

void Level::PlaceObject(MapEntry type, unsigned int amount)
{
	int current_amount = 0;

	while (current_amount != amount)
	{
		int i = Randomizer::GetInstance().Random(1, map_.size() - 2);
		int j = Randomizer::GetInstance().Random(1, map_.size() - 2);

		if (map_[i][j] == MapEntry::EMPTY && !HasNeighbors(i, j))
		{
			map_[i][j] = type;
			current_amount++;
		}
	}
}

void Level::SetupPassages()
{
	map_[1][map_.size() - 2] = MapEntry::ENTRANCE;
	map_[map_.size() - 2][1] = MapEntry::EXIT;
}

void Level::SetupEnemies()
{
	PlaceObject(MapEntry::ENEMY, 2);
}

void Level::SetupConsumables()
{
	PlaceObject(MapEntry::HEALTH_POUCH, 1);
	PlaceObject(MapEntry::OXYGEN_CAN, 1);
}

