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

Mesh *MeshFactory::CreateCube(unsigned int edge_size, glm::vec3 position, Material *material)
{
	Vertex v1, v2, v3, v4, v5, v6, v7, v8;

	float px = position.x;
	float py = position.y;
	float e = edge_size / 2;

	v1.position = { px-e, py-e, -e };
	v1.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v2.position = { px-e, py+e, -e };
	v2.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v3.position = { px+e, py+e, -e };
	v3.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v4.position = { px+e, py-e, -e };
	v4.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v5.position = { px-e, py-e, e };
	v5.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v6.position = { px-e, py+e, e };
	v6.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v7.position = { px+e, py+e, e };
	v7.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	v8.position = { px+e, py-e, e };
	v8.color = { 0.4f, 0.5f, 0.6f, 1.0f };

	std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0, // front face
		0, 1, 5, 5, 4, 0, // left side face
		0, 3, 7, 7, 4, 0, // bottom face
		6, 7, 4, 4, 5, 6, // back face
		6, 7, 3, 3, 2, 6, // right side face
		6, 2, 1, 1, 5, 6 // top face
	};

	return new Mesh({ v1, v2, v3, v4, v5, v6, v7, v8 }, indices, material);
}
