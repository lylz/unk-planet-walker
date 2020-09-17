#pragma once

#include "Font.h"
#define GLYPHS_COUNT 128

class FontLoader
{
public:
	static Font Load(std::string file_path);
};

