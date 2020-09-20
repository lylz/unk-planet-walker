#include "Level.h"
#include "game-objects/Wall.h"
#include "game-objects/Passage.h"
#include "game-objects/Enemy.h"
#include "game-objects/OxygenCan.h"
#include "game-objects/HealthPouch.h"
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
	float point = 4 * (map_.size() / 2);
	glm::vec2 top_left = glm::vec2(-point, point);

	for (unsigned int i = 0; i < map_.size(); i++)
	{
		for (unsigned int j = 0; j < map_.size(); j++)
		{
			glm::vec2 position = top_left + glm::vec2(4.0f * i, -4.0f * j);

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

	float point = 4 * (map_.size() / 2);
	glm::vec2 top_left = glm::vec2(-point, point);

	while (current_amount != amount)
	{
		int i = Randomizer::GetInstance().Random(1, map_.size() - 2);
		int j = Randomizer::GetInstance().Random(1, map_.size() - 2);

		if (map_[i][j] == MapEntry::EMPTY && !HasNeighbors(i, j))
		{
			glm::vec2 position = top_left + glm::vec2(4.0f * i, -4.0f * j);
			map_[i][j] = type;
			
			switch (type)
			{
			case MapEntry::OBSTACLE:
				game_objects_.push_back(new Wall(WallType::TOPDOWN, glm::vec3(position, 0)));
				break;
			case MapEntry::ENTRANCE:
				game_objects_.push_back(new Passage(PassageType::ENTRANCE, glm::vec3(position, 0)));
				break;
			case MapEntry::EXIT:
				game_objects_.push_back(new Passage(PassageType::EXIT, glm::vec3(position, 0)));
				break;
			case MapEntry::OXYGEN_CAN:
				game_objects_.push_back(new OxygenCan(glm::vec3(position, 0)));
				break;
			case MapEntry::HEALTH_POUCH:
				game_objects_.push_back(new HealthPouch(glm::vec3(position, 0)));
				break;
			case MapEntry::ENEMY:
				game_objects_.push_back(new Enemy(glm::vec3(position, 0)));
				break;
			}
			
			current_amount++;
		}
	}
}

void Level::SetupPassages()
{
	float point = 4 * (map_.size() / 2);
	glm::vec2 top_left = glm::vec2(-point, point);
	int i, j;

	{
		i = 1;
		j = map_.size() - 2;
		map_[i][j] = MapEntry::ENTRANCE;
		glm::vec2 position = top_left + glm::vec2(4.0f * i, -4.0f * j);
		game_objects_.push_back(new Passage(PassageType::ENTRANCE, glm::vec3(position, 0)));
	}

	{
		i = map_.size() - 2;
		j = 1;
		map_[i][j] = MapEntry::EXIT;
		glm::vec2 position = top_left + glm::vec2(4.0f * i, -4.0f * j);
		game_objects_.push_back(new Passage(PassageType::EXIT, glm::vec3(position, 0)));
	}
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

std::vector<GameObject *> Level::game_objects()
{
	return game_objects_;
}

Level::~Level()
{
	game_objects_.clear();
}

