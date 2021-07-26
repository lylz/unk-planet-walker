#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "game-objects/Enemy.h"
#include "game-objects/HealthPouch.h"
#include "game-objects/OxygenCan.h"
#include "game-objects/Passage.h"
#include "game-objects/Player.h"
#include "game-objects/Wall.h"

class Level
{
public:
	Level(unsigned int size);
	~Level();

	std::vector<std::vector<std::vector<GameObject *>>> map();
	std::vector<GameObject *> static_game_objects();
	std::vector<GameObject *> dynamic_game_objects();

	glm::vec3 CalculateInWorldPosition(unsigned int map_x, unsigned int map_y);
	glm::vec2 GetGameObjectPositionById(unsigned int id);
	void SetGameObjectPositionById(unsigned int id, glm::vec2 position);

private:
	std::vector<std::vector<std::vector<GameObject *>>> map_;
	std::vector<GameObject *> static_game_objects_;
	std::vector<GameObject *> dynamic_game_objects_;

	void PlacePlayer();
	void PlaceEnemy();
	void PlaceWalls();
	void PlaceObstacles();
	void PlacePassages();
	void PlaceConsumables();
};

