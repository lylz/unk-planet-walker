#pragma once

#include <vector>
#include "../utils/GLIncludes.h"
#include "shaders/Shader.h"
#include "Renderable.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Submit(Mesh *mesh);
	void Prepare();
	void Render();

private:
	Shader *default_shader_;
	std::vector<Renderable*> renderables_;
};

