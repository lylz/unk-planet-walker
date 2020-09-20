#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

Texture::Texture(const char *name, const char *file_path, const char *atlas_info_file_path)
	: Resource(name)
{
	stbi_uc *image_pixels = stbi_load(file_path, &width_, &height_, &channels_, STBI_rgb_alpha);

	if (!image_pixels)
	{
		throw std::runtime_error("ERROR: unable to load texture image.\n");
	}

	GLWCall(glGenTextures(1, &id_));
	GLWCall(glBindTexture(GL_TEXTURE_2D, id_));
	GLWCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLWCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLWCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
	GLWCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
	GLWCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_pixels));
	GLWCall(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(image_pixels);

	if (!atlas_info_file_path)
	{
		SpriteInfo info;
		info.name = name;
		info.position = { 0, 0 };
		info.size = { width_, height_ };
		info.uv = { 0, 0, 1, 1 };

		sprites_.push_back(info);
	}
	else
	{
		ParseAtlasInfo(atlas_info_file_path);
	}
}

Texture::Texture(const char *name, const char *file_path)
	: Texture(name, file_path, nullptr)
{}

void Texture::ParseAtlasInfo(const char *file_path)
{
	using namespace rapidjson;

	std::ifstream atlas(file_path);
	IStreamWrapper atlas_isw(atlas);

	Document document;
	document.ParseStream(atlas_isw);

	assert(document.IsObject() && document.HasMember("frames") && document["frames"].IsArray());

	const Value &frames = document["frames"];

	for (SizeType i = 0; i < frames.Size(); i++)
	{
		SpriteInfo frame_info;

		frame_info.name = frames[i]["name"].GetString();
		frame_info.position.x = frames[i]["frame"]["x"].GetFloat();
		frame_info.position.y = frames[i]["frame"]["y"].GetFloat();
		frame_info.size.x = frames[i]["frame"]["w"].GetFloat();
		frame_info.size.y = frames[i]["frame"]["h"].GetFloat();
		frame_info.uv.x = frame_info.position.x / width_;
		frame_info.uv.y = frame_info.position.y / height_;
		frame_info.uv.z = frame_info.uv.x + frame_info.size.x / width_;
		frame_info.uv.w = frame_info.uv.y + frame_info.size.y / height_;

		sprites_.push_back(frame_info);
	}
}

std::vector<SpriteInfo> Texture::sprites()
{
	return sprites_;
}

SpriteInfo Texture::GetSpriteInfo(const char *name)
{
	for (SpriteInfo sprite_info : sprites_)
	{
		if (sprite_info.name == name)
		{
			return sprite_info;
		}
	}
}

GLuint Texture::id()
{
	return id_;
}

int Texture::width()
{
	return width_;
}

int Texture::height()
{
	return height_;
}

void Texture::Bind(unsigned int slot)
{
	GLWCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLWCall(glBindTexture(GL_TEXTURE_2D, id_));
}

void Texture::Unbind(unsigned int slot)
{
	GLWCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLWCall(glBindTexture(GL_TEXTURE_2D, 0));
}
