#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

class Player: public GameObject
{
public:
	Player();
	~Player();

	void OnUpdate();

private:
	glm::vec3 position_;
	float speed_;
	DynamicObjectMaterial *material_;
};

