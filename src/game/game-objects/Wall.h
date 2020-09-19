#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

class Wall: public GameObject
{
public:
	Wall();
	~Wall();

	void OnUpdate();

private:
	DynamicObjectMaterial *material_;
};

