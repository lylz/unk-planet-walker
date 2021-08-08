#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

class OxygenCan: public GameObject
{
public:
	OxygenCan(glm::vec2 position);
	~OxygenCan();

    void OnUpdate();

private:
	DynamicObjectMaterial *material_;
};

