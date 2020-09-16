#include "Renderable.h"

Renderable::Renderable(Mesh *mesh)
	: mesh_(mesh)
{

	CreateVAO();
	CreateVBO();
	CreateIBO();
}

void Renderable::CreateVAO()
{
	glGenVertexArrays(1, &vao_id_);
	glBindVertexArray(vao_id_);
}

void Renderable::CreateVBO()
{
	glGenBuffers(1, &vbo_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
	glBufferData(GL_ARRAY_BUFFER, mesh_->vertices().size() * sizeof(Vertex), mesh_->vertices().data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv));
}

void Renderable::CreateIBO()
{
	glGenBuffers(1, &ibo_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_->indices().size() * sizeof(unsigned int), mesh_->indices().data(), GL_STATIC_DRAW);
}

Mesh *Renderable::mesh()
{
	return mesh_;
}

void Renderable::Prepare()
{
	glBindVertexArray(vao_id_);
}

void Renderable::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, mesh_->indices().size(), GL_UNSIGNED_INT, 0);
}
