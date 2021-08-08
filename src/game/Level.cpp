#include "Level.h"
#include "../utils/Randomizer.h"

Level::Level(unsigned int size)
{
	map_size_ = size;

    // NOTE: should place Consumables first in order for them to be rendered first
    // so that Player will be displayed on top of them.
    // Maybe add some texture order sort mechanicsm in the future.
	PlaceConsumables();
	PlacePlayer();
	PlaceEnemy();
	PlaceWalls();
	PlaceObstacles();
	PlacePassages();
}

Level::~Level()
{
    for (unsigned int i = 0; i < game_objects_.size(); i++)
    {
        delete game_objects_[i];
    }

    game_objects_.clear();
}

std::vector<GameObject *> Level::game_objects()
{
    return game_objects_;
}

void Level::SetGameObjectsBeforeDestroyCallback(void *context, void (*callback) (void *, GameObject *))
{
    game_objects_before_destroy_callback_ = callback;
    game_objects_before_destroy_callback_context_ = context;
}

void Level::DestroyGameObjectById(unsigned int id)
{
    GameObject *game_object = nullptr;

    for (unsigned int i = 0; i < game_objects_.size(); i++)
    {
        if (game_objects_[i]->id() == id)
        {
            game_object = game_objects_[i];
            break;
        }
    }

    assert(game_object != nullptr); // TODO: make proper check

    if (
        game_objects_before_destroy_callback_ != nullptr &&
        game_objects_before_destroy_callback_context_ != nullptr
    )
    {
        // TODO: giving the pointer outside, check it here and everywhere else
        game_objects_before_destroy_callback_(
            game_objects_before_destroy_callback_context_,
            game_object
        );
    }

    for (unsigned int i = 0; i < game_objects_.size(); i++)
    {
        if (game_objects_[i]->id() == game_object->id())
        {
            game_objects_.erase(game_objects_.begin() + i);
        }
    }

    delete game_object;
}

std::vector<GameObject *> Level::GetGameObjectsAtPosition(glm::vec2 position)
{
    std::vector<GameObject *> game_objects;

    for (auto game_object : game_objects_)
    {
        if (game_object->position() == position)
        {
            game_objects.push_back(game_object);
        }
    }

    return game_objects;
}

unsigned int Level::map_size()
{
    return map_size_;
}

// NOTE: returns only the first GameObject found
GameObject *Level::GetGameObjectByName(const std::string &name)
{
    for (auto game_object : game_objects_)
    {
        if (game_object->name() == name)
        {
            return game_object;
        }
    }
}

void Level::PlaceObstacles()
{
	Wall *obstacle = new Wall(WallType::TOPDOWN, { 7, 7 });

    game_objects_.push_back(obstacle);
}

void Level::PlacePlayer()
{
	Player *player = new Player({ 1, 1 });

    game_objects_.push_back(player);
}

void Level::PlaceEnemy()
{
	Enemy *enemy = new Enemy({ 4, 4 });

    game_objects_.push_back(enemy);
}

void Level::PlaceWalls()
{
	for (unsigned int i = 0; i < map_size_; i++)
	{
		for (unsigned int j = 0; j < map_size_; j++)
		{
			if (i == 0 || i == map_size_ - 1 || j == 0 || j == map_size_ - 1)
			{
				Wall *wall = nullptr;

				glm::vec2 position = { i, j };

				if (i == 0 || i == map_size_ - 1)
				{
					wall = new Wall(WallType::LEFT_SIDE, position);
				}
				else if (j == 0 || j == map_size_ - 1) {
					wall = new Wall(WallType::TOPDOWN, position);
				}

				if (wall != nullptr)
				{
                    game_objects_.push_back(wall);
				}
			}
		}
	}
}

void Level::PlacePassages()
{
	Passage *entrance = new Passage(PassageType::ENTRANCE, { 1, 1 });
	Passage *exit = new Passage(PassageType::EXIT, { map_size_ - 2, map_size_ - 2 });

    // NOTE: we don't need an entrance on the map, because it is not used in game logic at all
    game_objects_.push_back(exit);
    game_objects_.push_back(entrance);
}

void Level::PlaceConsumables()
{
	HealthPouch *health_pouch = new HealthPouch({ 2, 2 });
	OxygenCan *oxygen_can = new OxygenCan({ 5, 5 });

    game_objects_.push_back(health_pouch);
    game_objects_.push_back(oxygen_can);
}

