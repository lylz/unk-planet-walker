#include "MeshFactory.h"

Mesh *MeshFactory::CreateQuad(float width, float height, Material *material)
{
	return CreateQuad(width, height, { 0, 0 }, material);
}

Mesh *MeshFactory::CreateQuad(float width, float height, glm::vec2 position, Material *material)
{
	Vertex v1, v2, v3, v4;

	float px = position.x;
	float py = position.y;
	float w = width;
	float h = height;

	v1.position = { px-w, py-h, 0.0f };
	v1.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v1.uv = { 0, 1 };

	v2.position = { px-w, py+h, 0.0f };
	v2.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v2.uv = { 0, 0 };

	v3.position = { px+w, py+h, 0.0f };
	v3.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v3.uv = { 1, 0 };

	v4.position = { px+w, py-h, 0.0f };
	v4.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v4.uv = { 1, 1 };

	std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

	return new Mesh({ v1, v2, v3, v4 }, indices, material);
}
