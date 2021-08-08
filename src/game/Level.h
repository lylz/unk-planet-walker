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

    unsigned int map_size();
	std::vector<GameObject *> game_objects();

	glm::vec2 GetGameObjectPositionById(unsigned int id);
    std::vector<GameObject *> GetGameObjectsAtPosition(glm::vec2 position);
    GameObject *GetGameObjectByName(const std::string &name);
	glm::vec3 CalculateInWorldPosition(unsigned int map_x, unsigned int map_y);

    void SetGameObjectsBeforeDestroyCallback(void *context, void (*callback) (void *, GameObject *));
    void DestroyGameObjectById(unsigned int id);

private:
    unsigned int map_size_;
    std::vector<GameObject *> game_objects_;

    // TODO: make a list of callbacks, so that I can use the callback in different places simultaniously
    void (*game_objects_before_destroy_callback_) (void *, GameObject *);
    void *game_objects_before_destroy_callback_context_;

private:
	void PlacePlayer();
	void PlaceEnemy();
	void PlaceWalls();
	void PlaceObstacles();
	void PlacePassages();
	void PlaceConsumables();

};

