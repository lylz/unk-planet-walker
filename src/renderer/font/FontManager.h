#pragma once

#include <vector>
#include "Font.h"

// TODO: check all other asset managers,
// maybe it is worth writing one asset manager instead of multiple
// coz the logic is the same

class FontManager
{
public:
	static FontManager &GetInstance();

	void Add(Font font);
	Font Get(const char *name);
	void Remove(const char *name);

	FontManager(const FontManager &) = delete;
	void operator=(const FontManager &) = delete;

private:
	FontManager();

	std::vector<Font> fonts_;
};

