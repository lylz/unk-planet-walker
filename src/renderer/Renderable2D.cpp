#include "Renderable2D.h"

std::vector<Vertex> CreateQuad()
{
	Vertex v1, v2, v3, v4;

	v1.position = { -0.25f, -0.25f, 0.0f };
	v1.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v1.uv = { 0, 0 };

	v2.position = { -0.25f, 0.25f, 0.0f };
	v2.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v2.uv = { 0, 1 };

	v3.position = { 0.25f, 0.25f, 0.0f };
	v3.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v3.uv = { 1, 1 };

	v4.position = { 0.25f, -0.25f, 0.0f };
	v4.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v4.uv = { 1, 0 };

	return { v1, v2, v3, v4 };
}

std::vector<Vertex> CreateShape(int width, int height, float scale)
{
	Vertex v1, v2, v3, v4;

	float w = width * scale;
	float h = height * scale;

	v1.position = { -w, -h, 0.0f };
	v1.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v1.uv = { 0, 1 };

	v2.position = { -w, h, 0.0f };
	v2.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v2.uv = { 0, 0 };

	v3.position = { w, h, 0.0f };
	v3.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v3.uv = { 1, 0 };

	v4.position = { w, -h, 0.0f };
	v4.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v4.uv = { 1, 1 };

	return { v1, v2, v3, v4 };
}

Renderable2D::Renderable2D(Material *material)
	: IRenderable(material)
{
	if (material_ != nullptr && material_->texture() != nullptr)
	{
		Texture *texture = material_->texture();

		vertices_ = CreateShape(texture->width(), texture->height(), 1 / 8.0f);
	}
	else
	{
		vertices_ = CreateQuad();
	}

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv));
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
