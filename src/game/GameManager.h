#pragma once

#include "Level.h"

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

	Level *level_;
};

