#pragma once

#include "materials/Material.h"

class IRenderable
{
public:
	IRenderable(Material *material) : material_(material) {};

	inline Material *material() { return material_; };

	virtual void Prepare() = 0;
	virtual void Draw() = 0;

protected:
	Material *material_;
};
