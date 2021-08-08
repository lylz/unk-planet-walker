#include "GameManager.h"

GameManager &GameManager::GetInstance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
	level_ = nullptr;

	player_stats_ = new PlayerStats();
	player_stats_->hp = 300;
	player_stats_->oxygen = 300;
}

GameManager::~GameManager()
{
	delete level_;
}

void GameManager::GenerateLevel()
{
	if (level_ != nullptr)
	{
		delete level_;
	}

	level_ = new Level(10);
}

void GameManager::ConsumeHealthPouch()
{
    player_stats_->hp += HEALTH_POUCH_POINTS;
}

void GameManager::ConsumeOxygenCan()
{
    player_stats_->oxygen += OXYGEN_CAN_POINTS;
}

void GameManager::DescreasePlayerStats()
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

