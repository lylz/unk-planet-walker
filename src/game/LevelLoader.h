#pragma once

#include <string>
#include "LevelConfig.h"

class LevelLoader
{
 public:
    static LevelConfig Load(std::string file_path);
};
