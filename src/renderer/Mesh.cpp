#include "Mesh.h"

Mesh::Mesh(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	Material *material
)
	: vertices_(vertices),
	indices_(indices),
	material_(material)
{}

Material* Mesh::material()
{
	return material_;
}

std::vector<Vertex> Mesh::vertices()
{
	return vertices_;
}

std::vector<unsigned int> Mesh::indices()
{
	return indices_;
}
