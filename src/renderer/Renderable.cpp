#include "Renderable.h"

Renderable::Renderable()
    : Renderable(nullptr)
{};

// TODO: rethink the way I use Mesh in Renderable, currently missing assertion on mesh_ != nullptr
Renderable::Renderable(Mesh *mesh)
	: mesh_(mesh)
{

	CreateVAO();
	CreateVBO();
	CreateIBO();
}

void Renderable::CreateVAO()
{
	GLWCall(glGenVertexArrays(1, &vao_id_));
	GLWCall(glBindVertexArray(vao_id_));
}

void Renderable::CreateVBO()
{
	GLWCall(glGenBuffers(1, &vbo_id_));
	GLWCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_id_));
	GLWCall(glBufferData(GL_ARRAY_BUFFER, mesh_->vertices().size() * sizeof(Vertex), mesh_->vertices().data(), GL_STATIC_DRAW));

	GLWCall(glEnableVertexAttribArray(0));
	GLWCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position)));

	GLWCall(glEnableVertexAttribArray(1));
	GLWCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color)));

	GLWCall(glEnableVertexAttribArray(2));
	GLWCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv)));
}

void Renderable::CreateIBO()
{
	GLWCall(glGenBuffers(1, &ibo_id_));
	GLWCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_));
	GLWCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_->indices().size() * sizeof(unsigned int), mesh_->indices().data(), GL_STATIC_DRAW));
}

Mesh *Renderable::mesh()
{
	return mesh_;
}

void Renderable::Prepare()
{
	GLWCall(glBindVertexArray(vao_id_));
}

void Renderable::Draw()
{
	GLWCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	GLWCall(glDrawElements(GL_TRIANGLES, mesh_->indices().size(), GL_UNSIGNED_INT, 0));
}
