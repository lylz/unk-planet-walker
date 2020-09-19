#pragma once

#include "GameObject.h"

class Level
{
public:
	Level(unsigned int size);
	~Level();

	std::vector<Mesh *> meshes();

private:
	std::vector<GameObject*> game_objects_;

	void SetupWalls();
	void SetupPassages();
	void SetupEnemies();
	void SetupConsumables();
};

