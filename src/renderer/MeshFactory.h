#pragma once

#include "Mesh.h"

class MeshFactory
{
public:
	static Mesh *CreateQuad(glm::vec2 size, glm::vec4 color, glm::vec4 uv_origin, glm::vec3 position, Material *material);
    static Mesh *CreateQuad(glm::vec2 size, glm::vec4 uv, glm::vec3 position, Material *material);
	static Mesh *CreateQuad(glm::vec2 size, glm::vec3 position, Material *material);
	static Mesh *CreateQuad(glm::vec2 size, Material *material);
    static Mesh *CreateRectangle(unsigned int width, unsigned int height, glm::vec3 position, glm::vec4 color, Material *material);
	static Mesh *CreateCube(unsigned int edge_size, glm::vec3 position, Material *material);
};
