#pragma once

#include "Consumable.h"
#include "../../renderer/materials/default/TextureHolderMaterial.h"

class OxygenCan: public Consumable
{
public:
	OxygenCan(glm::vec3 position);
	~OxygenCan();

private:
	TextureHolderMaterial *material_;
};

