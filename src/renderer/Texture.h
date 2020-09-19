#pragma once

#include "../utils/GLIncludes.h"
#include "Resource.h"

class Texture: public Resource
{
public:
	Texture(const char *name, const char *file_path);

	GLuint id();
	int width();
	int height();

	void Bind(unsigned int slot);
	void Unbind(unsigned int slot);

private:
	GLuint id_;
	int width_;
	int height_;
	int channels_;
};

