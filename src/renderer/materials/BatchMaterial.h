#pragma once

#include <vector>
#include "Material.h"

class BatchMaterial: public Material
{
public:
	BatchMaterial(Shader *shader);

	void AddTexture(Texture *texture);
	void FlushTextures();

protected:
	std::vector<Texture *> textures_;
};
