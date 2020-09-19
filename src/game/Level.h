#pragma once

#include "GameObject.h"

enum class MapEntry
{
	WALL,
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
	~Level();

	std::vector<GameObject *> game_objects();

private:
	std::vector<std::vector<MapEntry>> map_;
	std::vector<GameObject*> game_objects_;

	void SetupWalls();
	void SetupPassages();
	void SetupEnemies();
	void SetupConsumables();
};

