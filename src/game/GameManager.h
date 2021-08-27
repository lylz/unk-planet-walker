#pragma once

#include <glm/glm.hpp>
#include "Level.h"

struct PlayerStats
{
	int hp;
	int oxygen;
};

// TODO: implement start stop mechanism
// TODO: maybe level shoudn't be a pointer
class GameManager
{
public:
	static GameManager &GetInstance();

	GameManager(const GameManager &) = delete;
	void operator=(const GameManager &) = delete;

    void ResetPlayerStats();
	void GenerateLevel();
    void ConsumeHealthPouch();
    void ConsumeOxygenCan();
	void DecreasePlayerStats();

	PlayerStats *player_stats();
	Level *level();
	
private:
	GameManager();
	~GameManager();

    const unsigned int DEPLETE_AMOUNT = 50;
    const unsigned int HEALTH_POUCH_POINTS = 50;
    const unsigned int OXYGEN_CAN_POINTS = 50;

	Level *level_;
	PlayerStats *player_stats_;
    bool game_over_;
};

