#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>

Texture::Texture(const char *file_path)
	: slot_(0)
{
	stbi_uc *image_pixels = stbi_load(file_path, &width_, &height_, &channels_, STBI_rgb_alpha);

	if (!image_pixels)
	{
		throw std::runtime_error("ERROR: unable to load texture image.\n");
	}

	// load
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image_pixels);
}

GLuint Texture::id()
{
	return id_;
}

unsigned int Texture::slot()
{
	return slot_;
}

int Texture::width()
{
	return width_;
}

int Texture::height()
{
	return height_;
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + slot_);
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind()
{
	glActiveTexture(GL_TEXTURE0 + slot_);
	glBindTexture(GL_TEXTURE_2D, 0);
}
