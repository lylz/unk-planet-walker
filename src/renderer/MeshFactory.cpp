#include "MeshFactory.h"

Mesh *MeshFactory::CreateQuad(glm::vec2 size, Material *material)
{
	return CreateQuad(size, { 0, 0, 0 }, material);
}

Mesh *MeshFactory::CreateQuad(glm::vec2 size, glm::vec3 position, Material *material)
{
	return CreateQuad(size, { 0, 0, 1, 1 }, position, material);
}

Mesh *MeshFactory::CreateQuad(glm::vec2 size, glm::vec4 uv, glm::vec3 position, Material *material)
{
	Vertex v1, v2, v3, v4;

	float px = position.x;
	float py = position.y;
	float w = size.x / 2;
	float h = size.y / 2;

	v1.position = { px-w, py-h, 0.0f };
	v1.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v1.uv = { uv.x, uv.w };

	v2.position = { px-w, py+h, 0.0f };
	v2.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v2.uv = { uv.x, uv.y };

	v3.position = { px+w, py+h, 0.0f };
	v3.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v3.uv = { uv.z, uv.y };

	v4.position = { px+w, py-h, 0.0f };
	v4.color = { 0.4f, 0.5f, 0.6f, 1.0f };
	v4.uv = { uv.z, uv.w };

	std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

	return new Mesh({ v1, v2, v3, v4 }, indices, material);
}
