#pragma once

#include "Mesh.h"

class MeshFactory
{
public:
	static Mesh *CreateQuad(glm::vec2 size, glm::vec4 uv_origin, glm::vec3 position, Material *material);
	static Mesh *CreateQuad(glm::vec2 size, glm::vec3 position, Material *material);
	static Mesh *CreateQuad(glm::vec2 size, Material *material);
};
