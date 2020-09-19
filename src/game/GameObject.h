#pragma once

#include "../renderer/Mesh.h"

class GameObject
{
public:
	inline Mesh *mesh() { return mesh_; };

	virtual void OnUpdate() = 0;

protected:
	Mesh *mesh_;
};
