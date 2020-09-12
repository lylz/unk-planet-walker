#pragma once

#include "../utils/GLIncludes.h"
#include "Renderable.h"
#include "./materials/BatchMaterial.h"

class BatchRenderer
{
public:
	BatchRenderer(BatchMaterial *global_material);
	~BatchRenderer();

	void Submit(Renderable *renderable);
	void Render();
	void Flush();

private:
	GLuint vertex_array_id_;
	GLuint vertex_buffer_id_;
	GLuint index_buffer_id_;

	BatchMaterial *global_material_;

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	unsigned int index_offset_ = 0;
};

