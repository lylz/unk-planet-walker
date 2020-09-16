#include "Renderable.h"

Renderable::Renderable(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	Material *material
)
	: vertices_(vertices),
	indices_(indices),
	material_(material)
{}

Material* Renderable::material()
{
	return material_;
}

std::vector<Vertex> Renderable::vertices()
{
	return vertices_;
}

std::vector<unsigned int> Renderable::indices()
{
	return indices_;
}
