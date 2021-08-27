#include "GameManager.h"

#include "LevelLoader.h"

GameManager &GameManager::GetInstance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
	level_ = nullptr;

	player_stats_ = new PlayerStats();
    ResetPlayerStats();
}

GameManager::~GameManager()
{
	delete level_;
}

void GameManager::ResetPlayerStats()
{
	player_stats_->hp = 300;
	player_stats_->oxygen = 300;
}

void GameManager::GenerateLevel()
{
	if (level_ != nullptr)
	{
		delete level_;
	}

    LevelConfig level_config = LevelLoader::Load("assets/levels/level1.json");

	level_ = new Level(level_config);
}

void GameManager::ConsumeHealthPouch()
{
    player_stats_->hp += HEALTH_POUCH_POINTS;
}

void GameManager::ConsumeOxygenCan()
{
    player_stats_->oxygen += OXYGEN_CAN_POINTS;
}

void GameManager::DecreasePlayerStats()
{
	if (player_stats_->oxygen > 0)
	{
		player_stats_->oxygen -= DEPLETE_AMOUNT;
	}
	else
	{
		player_stats_->hp -= DEPLETE_AMOUNT;
	}

	// TODO: if player_stats_->hp <= 0 then game_over
}

PlayerStats *GameManager::player_stats()
{
	return player_stats_;
}

Level *GameManager::level()
{
	return level_;
}

