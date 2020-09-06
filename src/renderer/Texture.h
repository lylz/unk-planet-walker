#pragma once

#include "../utils/GLIncludes.h"

class Texture
{
public:
	Texture(const char *file_path);

	GLuint id();
	unsigned int slot();
	int width();
	int height();

	void Bind();
	void Unbind();

private:
	GLuint id_;
	unsigned int slot_;
	int width_;
	int height_;
	int channels_;
};

