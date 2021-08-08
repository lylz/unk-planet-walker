#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/TextureHolderMaterial.h"

enum class WallType
{
	LEFT_SIDE,
	RIGHT_SIDE,
	TOPDOWN
};

class Wall: public GameObject
{
public:
	Wall(WallType type, glm::vec2 position);
	~Wall();

	void OnUpdate();

private:
	TextureHolderMaterial *material_;
};

