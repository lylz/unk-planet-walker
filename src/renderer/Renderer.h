#pragma once

#include <vector>
#include "../utils/GLIncludes.h"
#include "shaders/Shader.h"
#include "IRenderable.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Prepare();
	void Render(std::vector<IRenderable*> renderable_objects);

private:
	Shader *default_shader_;
};

