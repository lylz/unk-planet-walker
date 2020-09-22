#pragma once

#include <vector>

enum class MapEntry
{
	WALL,
	OBSTACLE,
	ENTRANCE,
	EXIT,
	HEALTH_POUCH,
	OXYGEN_CAN,
	ENEMY,
	EMPTY
};

class Level
{
public:
	Level(unsigned int size);

	std::vector<std::vector<MapEntry>> map();

private:
	std::vector<std::vector<MapEntry>> map_;

	void SetupWalls();
	void SetupObstacles();
	void SetupPassages();
	void SetupEnemies();
	void SetupConsumables();
	void PlaceObject(MapEntry type, unsigned int amount);
	bool HasNeighbors(int i, int j);
};

