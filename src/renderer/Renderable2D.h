#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../utils/GLIncludes.h"
#include "IRenderable.h"

struct Vertex
{
	glm::vec3 position;
};

class Renderable2D: public IRenderable
{
public:
	Renderable2D(Material *material);

	void Prepare();
	void Draw();

private:
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;

	GLuint vao_id_;
	GLuint vbo_id_;
	GLuint ibo_id_;

private:
	void CreateVAO();
	void CreateVBO();
	void CreateIBO();
};

