#include "Utils.h"

glm::vec3 CalculateInWorldPositionFromMapPosition(glm::vec2 map_position)
{
    float world_multiplier = 4.0f;

    return glm::vec3(map_position.x, map_position.y, 0) * world_multiplier;
}
