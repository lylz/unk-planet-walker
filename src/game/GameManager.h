#pragma once

#include <glm/glm.hpp>
#include "Level.h"

// TODO: implement start stop mechanism
// TODO: maybe level shoudn't be a pointer
class GameManager
{
public:
	static GameManager &GetInstance();

	GameManager(const GameManager &) = delete;
	void operator=(const GameManager &) = delete;

	void GenerateLevel();

	Level *level();
	
private:
	GameManager();
	~GameManager();

	Level *level_;
};

