#pragma once

#include <vector>
#include "../utils/GLIncludes.h"
#include "Renderable.h"
#include "Vertex.h"

class Renderable2D: public Renderable
{
public:
	Renderable2D(Material *material);

	void Prepare();
	void Draw();

private:
	GLuint vao_id_;
	GLuint vbo_id_;
	GLuint ibo_id_;

private:
	void CreateVAO();
	void CreateVBO();
	void CreateIBO();
};

