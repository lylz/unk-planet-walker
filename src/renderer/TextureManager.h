#pragma once

#include <vector>
#include "Texture.h"

class TextureManager
{
public:
	static TextureManager &GetInstance();

	void Add(Texture *texture);
	Texture *Get(const char *name);
	void Remove(const char *name);

	TextureManager(const TextureManager &) = delete;
	void operator=(const TextureManager &) = delete;

private:
	TextureManager();
	~TextureManager();

	std::vector<Texture *> textures_;
};

