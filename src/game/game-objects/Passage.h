#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/TextureHolderMaterial.h"

enum class PassageType
{
	ENTRANCE,
	EXIT
};

class Passage: public GameObject
{
public:
	Passage(PassageType type, glm::vec2 position);
	~Passage();

	void OnUpdate();
private:
	TextureHolderMaterial *material_;
};

