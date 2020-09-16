#pragma once

#include <map>
#include "../utils/GLIncludes.h"
#include "Mesh.h"
#include "./materials/BatchMaterial.h"

class BatchRenderer
{
public:
	BatchRenderer(BatchMaterial *global_material);
	~BatchRenderer();

	void Submit(Mesh *renderable);
	void Render();
	void Flush();

private:
	GLuint vertex_array_id_;
	GLuint vertex_buffer_id_;
	GLuint index_buffer_id_;

	BatchMaterial *global_material_;
	unsigned int texture_slot_index_;
	std::map<GLuint, unsigned int> textures_slots_map_;

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	unsigned int index_offset_ = 0;

	int GetTextureSlot(GLuint texture_id);
};

