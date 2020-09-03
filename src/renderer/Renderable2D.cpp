#include "Renderable2D.h"

std::vector<Vertex> CreateQuad()
{
	Vertex v1, v2, v3, v4;

	v1.position = { -0.25f, 0.25f, 0.0f };
	v2.position = { -0.25f, -0.25f, 0.0f };
	v3.position = { 0.25f, -0.25f, 0.0f };
	v4.position = { 0.25f, 0.25f, 0.0f };

	return { v1, v2, v3, v4 };
}

Renderable2D::Renderable2D()
{
	vertices_ = CreateQuad();
	indices_ = { 0, 1, 2, 2, 3, 0 };

	CreateVAO();
	CreateVBO();
	CreateIBO();
}

void Renderable2D::CreateVAO()
{
	glGenVertexArrays(1, &vao_id_);
	glBindVertexArray(vao_id_);
}

void Renderable2D::CreateVBO()
{
	glGenBuffers(1, &vbo_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), vertices_.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}

void Renderable2D::CreateIBO()
{
	glGenBuffers(1, &ibo_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);
}

void Renderable2D::Prepare()
{
	glBindVertexArray(vao_id_);
}

void Renderable2D::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}
