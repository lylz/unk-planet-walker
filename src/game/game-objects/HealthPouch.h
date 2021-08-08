#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

class HealthPouch: public GameObject
{
public:
	HealthPouch(glm::vec2 position);
	~HealthPouch();

    void OnUpdate();

private:
	DynamicObjectMaterial *material_;
};

