#pragma once

#include <vector>
#include <glm/glm.hpp>

enum struct LevelObjectType
{
    ENTRANCE,
    EXIT,
    PLAYER,
    ENEMY,
    OBSTACLE,
    HEALTH_POUCH,
    OXYGEN_CAN
};

struct LevelObject
{
    LevelObjectType type;
    glm::vec2 position;
};

struct LevelConfig
{
    unsigned int size;
    std::vector<LevelObject> objects;
};
