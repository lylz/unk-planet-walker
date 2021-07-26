#include "Level.h"
#include "../utils/Randomizer.h"

Level::Level(unsigned int size)
{
	map_.resize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		map_[i].resize(size);
	}

	PlacePlayer();
	PlaceEnemy();
	PlaceWalls();
	PlaceObstacles();
	PlacePassages();
	PlaceConsumables();
}

Level::~Level()
{
	for (unsigned int i = 0; i < map_.size(); i++)
	{
		for (unsigned int j = 0; j < map_[i].size(); j++)
		{
			for (unsigned int k = 0; k < map_[i][j].size(); k++)
			{
				delete map_[i][j][k];
			}
		}
	}

	static_game_objects_.clear();
	dynamic_game_objects_.clear();
}

std::vector<std::vector<std::vector<GameObject *>>> Level::map()
{
	return map_;
}

std::vector<GameObject *> Level::static_game_objects()
{
	return static_game_objects_;
}

std::vector<GameObject *> Level::dynamic_game_objects()
{
	return dynamic_game_objects_;
}

glm::vec2 Level::GetGameObjectPositionById(unsigned int id)
{
	for (unsigned int i = 0; i < map_.size(); i++)
	{
		for (unsigned int j = 0; j < map_[i].size(); j++)
		{
			for (unsigned int k = 0; k < map_[i][j].size(); k++)
			{
				GameObject *game_object = map_[i][j][k];

				if (game_object != nullptr && game_object->id() == id)
				{
					return glm::vec2(i, j);
				}
			}
		}
	}
}

void Level::SetGameObjectPositionById(unsigned int id, glm::vec2 position)
{
	glm::vec2 game_object_position = GetGameObjectPositionById(id);
	std::vector<GameObject *> game_objects = map_[game_object_position.x][game_object_position.y];

	GameObject *game_object = nullptr;

	for (unsigned int i = 0; i < game_objects.size(); i++)
	{
		if (game_objects[i]->id() == id)
		{
			game_object = game_objects[i];
			// TODO: check it
			map_[game_object_position.x][game_object_position.y].erase(map_[game_object_position.x][game_object_position.y].begin() + i);
			break;
		}
	}

	assert(game_object != nullptr);

	map_[position.x][position.y].push_back(game_object);
}

glm::vec3 Level::CalculateInWorldPosition(unsigned int map_x, unsigned int map_y)
{
	float world_coordinate_multiplier = 4.0f;

	return glm::vec3(map_x, map_y, 0) * world_coordinate_multiplier;
}

void Level::PlaceObstacles()
{
	Wall *obstacle = new Wall(WallType::TOPDOWN, CalculateInWorldPosition(7, 7));

	map_[7][7].push_back(obstacle);
	static_game_objects_.push_back(obstacle);
}

void Level::PlacePlayer()
{
	Player *player = new Player();

	map_[1][1].push_back(player);
	dynamic_game_objects_.push_back(player);
}

void Level::PlaceEnemy()
{
	Enemy *enemy = new Enemy(CalculateInWorldPosition(4, 4));

	map_[4][4].push_back(enemy);
	dynamic_game_objects_.push_back(enemy);
}

void Level::PlaceWalls()
{
	for (unsigned int i = 0; i < map_.size(); i++)
	{
		for (unsigned int j = 0; j < map_.size(); j++)
		{
			if (i == 0 || i == map_.size() - 1 || j == 0 || j == map_.size() - 1)
			{
				Wall *wall = nullptr;

				glm::vec3 position = CalculateInWorldPosition(i, j);

				if (i == 0 || i == map_.size() - 1)
				{
					wall = new Wall(WallType::LEFT_SIDE, position);
				}
				else if (j == 0 || j == map_.size() - 1) {
					wall = new Wall(WallType::TOPDOWN, position);
				}

				if (wall != nullptr)
				{
					map_[i][j].push_back(wall);
					static_game_objects_.push_back(wall);
				}
			}
		}
	}
}

void Level::PlacePassages()
{
	Passage *entrance = new Passage(PassageType::ENTRANCE, CalculateInWorldPosition(1, 1));
	Passage *exit = new Passage(PassageType::EXIT, CalculateInWorldPosition(map_.size() - 2, map_.size() - 2));

	map_[1][1].push_back(entrance);
	static_game_objects_.push_back(entrance);
	map_[map_.size() - 2][map_.size() - 2].push_back(exit);
	static_game_objects_.push_back(exit);
}

void Level::PlaceConsumables()
{
	HealthPouch *health_pouch = new HealthPouch(CalculateInWorldPosition(2, 2));
	OxygenCan *oxygen_can = new OxygenCan(CalculateInWorldPosition(5, 5));

	map_[2][2].push_back(health_pouch);
	static_game_objects_.push_back(health_pouch);
	map_[5][5].push_back(oxygen_can);
	static_game_objects_.push_back(oxygen_can);
}

