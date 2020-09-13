#include "BatchRenderer.h"

#define BATCH_RENDERER_MAX_OBJECTS   30000
#define BATCH_RENDERER_VERTEX_COUNT  4
#define BATCH_RENDERER_OBJECT_SIZE   sizeof(Vertex) * BATCH_RENDERER_VERTEX_COUNT
#define BATCH_RENDERER_BUFFER_SIZE   BATCH_RENDERER_MAX_OBJECTS * BATCH_RENDERER_OBJECT_SIZE
#define BATCH_RENDERER_INDICES_SIZE  BATCH_RENDERER_MAX_OBJECTS * 6

BatchRenderer::BatchRenderer(BatchMaterial *global_material)
{
	assert(global_material != nullptr);

	global_material_ = global_material;

	glGenVertexArrays(1, &vertex_array_id_);
	glBindVertexArray(vertex_array_id_);

	glGenBuffers(1, &vertex_buffer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, BATCH_RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, uv));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, texture_id));

	glGenBuffers(1, &index_buffer_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, BATCH_RENDERER_INDICES_SIZE, nullptr, GL_DYNAMIC_DRAW);
}

BatchRenderer::~BatchRenderer()
{
	glDeleteBuffers(1, &vertex_buffer_id_);
	glDeleteBuffers(1, &index_buffer_id_);
}

void BatchRenderer::Submit(Renderable *renderable)
{
	auto renderable_vertices = renderable->vertices();
	// TODO: allocate texture slots upfront, store them inside of vertices
	for (size_t i = 0; i < renderable_vertices.size(); i++)
	{
		Vertex v = renderable_vertices[i];
		v.texture_id = index_offset_ / BATCH_RENDERER_VERTEX_COUNT;

		vertices_.push_back(v);
	}

	auto renderable_indices = renderable->indices();

	for (size_t i = 0; i < renderable_indices.size(); i++)
	{
		indices_.push_back(renderable_indices[i] + index_offset_);
	}

	index_offset_ += BATCH_RENDERER_VERTEX_COUNT;

	if (renderable->material() != nullptr && renderable->material()->texture() != nullptr)
	{
		global_material_->AddTexture(renderable->material()->texture());
	}
}

void BatchRenderer::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	global_material_->Bind();

	glBindVertexArray(vertex_array_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_.size() * sizeof(Vertex), vertices_.data());
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices_.size() * sizeof(unsigned int), indices_.data());

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}

void BatchRenderer::Flush()
{
	vertices_.clear();
	indices_.clear();
	global_material_->FlushTextures();
	index_offset_ = 0;
}
