#include "Level.h"

Level::Level(unsigned int size)
{
	SetupWalls();
	SetupPassages();
	SetupEnemies();
	SetupConsumables();
}

void Level::SetupWalls()
{

}

void Level::SetupPassages()
{

}

void Level::SetupEnemies()
{

}

void Level::SetupConsumables()
{

}

std::vector<Mesh *> Level::meshes()
{
	std::vector<Mesh *> meshes;

	for (GameObject *game_object : game_objects_)
	{
		meshes.push_back(game_object->mesh());
	}

	return meshes;
}

Level::~Level()
{
	game_objects_.clear();
}

