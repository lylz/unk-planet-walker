#include "Mesh.h"

#include "../utils/IdentifierManager.h"

Mesh::Mesh()
    : Mesh({}, {}, nullptr)
{}

Mesh::Mesh(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	Material *material
)
	: vertices_(vertices),
	indices_(indices),
    material_(material),
    id_(IdentifierManager::GetInstance().GetNewIdentifier())
{}

unsigned int Mesh::id()
{
    return id_;
}

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

