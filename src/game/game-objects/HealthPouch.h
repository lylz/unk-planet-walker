#pragma once

#include "Consumable.h"
#include "../../renderer/materials/default/TextureHolderMaterial.h"

class HealthPouch: public Consumable
{
public:
	HealthPouch(glm::vec3 position);
	~HealthPouch();

private:
	TextureHolderMaterial *material_;
};

