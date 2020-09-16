#pragma once

#include "Mesh.h"

class MeshFactory
{
public:
	static Mesh *CreateQuad(float width, float height, glm::vec2 position, Material *material);
	static Mesh *CreateQuad(float width, float height, Material *material);
};
