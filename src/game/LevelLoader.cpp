#include "LevelLoader.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

LevelConfig LevelLoader::Load(std::string file_path)
{
    using namespace rapidjson;

    std::ifstream file(file_path);
    IStreamWrapper file_isw(file);

    Document document;
    document.ParseStream(file_isw);

    // TODO: make proper check
    assert(document.IsObject() && document.HasMember("size") && document.HasMember("objects") && document["objects"].IsArray());

    LevelConfig level_config;
    level_config.size = document["size"].GetUint();

    const Value &objects = document["objects"];

    for (SizeType i = 0; i < objects.Size(); i++)
    {
        LevelObject level_object;
        std::string object_type = objects[i]["type"].GetString();

        if (object_type == "ENTRANCE")
        {
            level_object.type = LevelObjectType::ENTRANCE;
        }
        else if (object_type == "EXIT")
        {
            level_object.type = LevelObjectType::EXIT;
        }
        else if (object_type == "PLAYER")
        {
            level_object.type = LevelObjectType::PLAYER;
        }
        else if (object_type == "ENEMY")
        {
            level_object.type = LevelObjectType::ENEMY;
        }
        else if (object_type == "OBSTACLE")
        {
            level_object.type = LevelObjectType::OBSTACLE;
        }
        else if (object_type == "HEALTH_POUCH")
        {
            level_object.type = LevelObjectType::HEALTH_POUCH;
        }
        else if (object_type == "OXYGEN_CAN")
        {
            level_object.type = LevelObjectType::OXYGEN_CAN;
        }

        auto position = objects[i]["position"].GetArray();

        // NOTE: in json file the positions are stored in a way that Y is the first member,
        // and X is the second member
        level_object.position.x = position[1].GetInt();
        level_object.position.y = position[0].GetInt();

        level_config.objects.push_back(level_object);
    }

    return level_config;
}
