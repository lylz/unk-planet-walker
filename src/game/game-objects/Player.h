#pragma once

#include "../GameObject.h"
#include "../../application/Timer.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

class Player: public GameObject
{
public:
	Player();
	~Player();

	void OnUpdate();

private:
	DynamicObjectMaterial *material_;
	Timer move_timer_;
	long double move_start_time_;

private:
	void Update();
	void Move(glm::vec2 step);
};

