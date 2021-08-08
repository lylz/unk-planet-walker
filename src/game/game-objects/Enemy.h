#pragma once

#include "../GameObject.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"

/*
	looks like the following, where:
	"E" - enemy position
	"x" - radius point
	"-" - irrelevant to the enemy point on the map

	--x--
	-xxx-
	xxExx
	-xxx-
	--x--
*/
const std::vector<glm::vec2> ObserveDirections = {
	{-1, 0}, {-1, 1}, {-1, -1}, {-2, 0},
	{1, 0},	{1, 1},	{1, -1}, {2, 0},
	{0, 1},	{0, 2},	{0, -1}, {0, -2}
};

class Enemy: public GameObject
{
public:
	Enemy(glm::vec2 position);
	~Enemy();

	void OnUpdate();
	void TakeTurn();

private:
	DynamicObjectMaterial *material_;

private:
	void ObserveSurroundings();
};

