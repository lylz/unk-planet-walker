#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "../utils/GLIncludes.h"
#include "Resource.h"

struct SpriteInfo
{
	std::string name;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec4 uv;
};

class Texture: public Resource
{
public:
	Texture(const char *name, const char *file_path);
	Texture(const char *name, const char *file_path, const char *atlas_info_file_path);

	GLuint id();
	int width();
	int height();

	void Bind(unsigned int slot);
	void Unbind(unsigned int slot);

	SpriteInfo GetSpriteInfo(const char *name);
	std::vector<SpriteInfo> sprites();

private:
	GLuint id_;
	int width_;
	int height_;
	int channels_;

	std::vector<SpriteInfo> sprites_;

	void ParseAtlasInfo(const char *file_path);
};

