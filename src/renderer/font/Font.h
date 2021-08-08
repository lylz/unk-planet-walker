#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

struct GlyphInfo
{
	int x0, y0, x1, y1;
	glm::ivec2 size;
	glm::ivec2 bearing;
	int advance;
};

struct Font
{
	std::string name;
	int size;
	std::unordered_map<char, GlyphInfo> glyphs;
	std::string atlas_path;
	glm::ivec2 atlas_size;
};
