#include "Level.h"
#include "game-objects/Wall.h"

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
	SetupPassages();
	SetupEnemies();
	SetupConsumables();
}

void Level::SetupWalls()
{
	int point = 5 * (map_.size() / 2);
	glm::vec2 top_left = glm::vec2(-point, point);

	for (unsigned int i = 0; i < map_.size(); i++)
	{
		for (unsigned int j = 0; j < map_.size(); j++)
		{
			glm::vec2 position = top_left + glm::vec2(5.0f * i, -5.0f * j);

			if (i == 0 || i == map_.size() - 1)
			{
				game_objects_.push_back(new Wall(WallType::LEFT_SIDE, glm::vec3(position, 0)));
				map_[i][j] = MapEntry::WALL;
			}

			if (j == 0 || j == map_.size() - 1)
			{
				game_objects_.push_back(new Wall(WallType::TOPDOWN, glm::vec3(position, 0)));
				map_[i][j] = MapEntry::WALL;

			}
		}
	}
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

std::vector<GameObject *> Level::game_objects()
{
	return game_objects_;
}

Level::~Level()
{
	game_objects_.clear();
}

