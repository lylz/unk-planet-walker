#pragma once

#include <vector>
#include "../utils/GLIncludes.h"
#include "Mesh.h"

class Renderable
{
public:
    Renderable();
	Renderable(Mesh *mesh);

	void Prepare();
	void Draw();

	Mesh *mesh();

private:
	Mesh *mesh_;

	GLuint vao_id_;
	GLuint vbo_id_;
	GLuint ibo_id_;

private:
	void CreateVAO();
	void CreateVBO();
	void CreateIBO();
};

