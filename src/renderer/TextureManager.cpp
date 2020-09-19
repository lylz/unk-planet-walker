#include "TextureManager.h"

TextureManager::TextureManager()
{}

TextureManager &TextureManager::GetInstance()
{
	static TextureManager instance;

	return instance;
}

TextureManager::~TextureManager()
{
	for (unsigned int i = 0; i < textures_.size(); i++)
	{
		delete textures_[i];
	}
}

void TextureManager::Add(Texture *texture)
{
	textures_.push_back(texture);
}

Texture *TextureManager::Get(const char *name)
{
	for (Texture *texture : textures_)
	{
		if (texture->name() == name)
		{
			return texture;
		}
	}

	return nullptr;
}

void TextureManager::Remove(const char *name)
{
	for (unsigned int i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];

		if (texture->name() == name)
		{
			delete texture;
			textures_.erase(textures_.begin() + i);
			return;
		}
	}
}
