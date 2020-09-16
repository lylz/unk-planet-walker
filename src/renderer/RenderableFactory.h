#pragma once

#include "Renderable.h"

class RenderableFactory
{
public:
	static Renderable *CreateQuad(float width, float height, glm::vec2 position, Material *material);
	static Renderable *CreateQuad(float width, float height, Material *material);
};
