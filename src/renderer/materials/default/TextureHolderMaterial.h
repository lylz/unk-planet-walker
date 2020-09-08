#pragma once

#include "../Material.h"

class TextureHolderMaterial : public Material
{
public:
	inline TextureHolderMaterial(Texture *texture) : Material(nullptr, texture) {};

	inline void Bind() {};
	inline void Unbind() {};
};

