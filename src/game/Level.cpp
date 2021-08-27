#include "Level.h"
#include "../utils/Randomizer.h"

Level::Level(LevelConfig level_config)
{
	map_size_ = level_config.size;

    // NOTE: should place Consumables first in order for them to be rendered first
    // so that Player will be displayed on top of them.
    // Maybe add some texture order sort mechanicsm in the future.
    for (auto level_object : level_config.objects)
    {
        GameObject *game_object;

        switch (level_object.type)
        {
        case LevelObjectType::ENTRANCE:
            game_object = new Passage(PassageType::ENTRANCE, level_object.position);
            break;
        case LevelObjectType::EXIT:
            game_object = new Passage(PassageType::EXIT, level_object.position);
            break;
        case LevelObjectType::PLAYER:
            game_object = new Player(level_object.position);
            break;
        case LevelObjectType::ENEMY:
            game_object = new Enemy(level_object.position);
            break;
        case LevelObjectType::OBSTACLE:
            game_object = new Wall(WallType::TOPDOWN, level_object.position);
            break;
        case LevelObjectType::HEALTH_POUCH:
            game_object = new HealthPouch(level_object.position);
            break;
        case LevelObjectType::OXYGEN_CAN:
            game_object = new OxygenCan(level_object.position);
            break;
        }

        game_objects_.push_back(game_object);
    }

	PlaceWalls();
}

Level::~Level()
{
    for (unsigned int i = 0; i < game_objects_.size(); i++)
    {
        delete game_objects_[i];
    }

    game_objects_.clear();
}

const std::vector<GameObject *> &Level::game_objects()
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
    int game_object_index = -1;
    
    for (unsigned int i = 0; i < game_objects_.size(); i++)
    {
        if (game_objects_[i]->id() == id)
        {
            game_object = game_objects_[i];
            game_object_index = i;
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

    game_objects_.erase(game_objects_.begin() + game_object_index);
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

    return nullptr;
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

