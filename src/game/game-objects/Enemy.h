#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

class Enemy: public GameObject
{
public:
	Enemy(glm::vec3 position);
	~Enemy();

	void OnUpdate();

private:
	DynamicObjectMaterial *material_;
};

