#pragma once

#include <vector>
#include <map>
#include "Material.h"

class BatchMaterial: public Material
{
public:
	BatchMaterial(Shader *shader);

	void AddTexture(Texture *texture, unsigned int slot);
	void FlushTextures();

protected:
	std::vector<Texture*> textures_;
	std::map<GLuint, unsigned int> textures_slots_map_;
};
