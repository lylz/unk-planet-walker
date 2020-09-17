#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#define GLYPHS_COUNT 128

struct GlyphInfo
{
	int x0, y0, x1, y1;
	glm::ivec2 size;
	glm::ivec2 bearing;
	int advance;
};

struct Font
{
	int size;
	std::unordered_map<char, GlyphInfo> glyphs;
	std::string atlas_path;
	glm::ivec2 atlas_size;
};

class FontLoader
{
public:
	static Font Load(std::string file_path);
};

