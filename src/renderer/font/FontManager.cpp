#include "FontManager.h"

FontManager::FontManager()
{}

FontManager &FontManager::GetInstance()
{
	static FontManager instance;

	return instance;
}

void FontManager::Add(Font font)
{
	fonts_.push_back(font);
}

Font FontManager::Get(const char *name)
{
	for (Font font : fonts_)
	{
		if (font.name == name)
		{
			return font;
		}
	}
}

void FontManager::Remove(const char *name)
{
	for (unsigned int i = 0; i < fonts_.size(); i++)
	{
		Font font = fonts_[i];

		if (font.name == name)
		{
			fonts_.erase(fonts_.begin() + i);
			return;
		}
	}
}