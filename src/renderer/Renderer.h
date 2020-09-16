#pragma once

#include <vector>
#include "../utils/GLIncludes.h"
#include "shaders/Shader.h"
#include "Renderable2D.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Prepare();
	void Render(std::vector<Renderable2D*> renderable_objects);

private:
	Shader *default_shader_;
};

