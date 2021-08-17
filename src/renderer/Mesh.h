#pragma once

#include <vector>
#include "Vertex.h"
#include "materials/Material.h"

class Mesh
{
public:
    Mesh();
	Mesh(
		std::vector<Vertex> vertices,
		std::vector<unsigned int> indices,
		Material *material
	);

    unsigned int id();
	Material *material();
	std::vector<Vertex> vertices();
	std::vector<unsigned int> indices();

protected:
    unsigned int id_;

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	Material *material_;
};
