#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/TextureHolderMaterial.h"

class Enemy: public GameObject
{
public:
	Enemy(glm::vec3 position);
	~Enemy();

	void OnUpdate();

private:
	TextureHolderMaterial *material_;
};

