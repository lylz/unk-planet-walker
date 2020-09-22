#include "GameManager.h"

GameManager &GameManager::GetInstance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
	level_ = nullptr;
}

void GameManager::GenerateLevel()
{
	if (level_ != nullptr)
	{
		delete level_;
	}

	level_ = new Level(10);
}

Level *GameManager::level()
{
	return level_;
}
