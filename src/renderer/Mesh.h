#pragma once

#include <vector>
#include "Vertex.h"
#include "materials/Material.h"

class Mesh
{
public:
	Mesh(
		std::vector<Vertex> vertices,
		std::vector<unsigned int> indices,
		Material *material
	);

	Material *material();
	std::vector<Vertex> vertices();
	std::vector<unsigned int> indices();

protected:
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	Material *material_;
};
