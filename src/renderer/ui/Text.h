#pragma once

#include "../font/Font.h"
#include "../Mesh.h"

class Text
{
public:
	Text(std::string text, Font font, glm::vec2 screen_position);
	~Text();

	std::vector<Mesh *> meshes();

private:
	std::string text_;
	Font font_;
	Texture *font_atlas_texture_;
	Material *material_;
	std::vector<Mesh *> meshes_;
    float x_;
    float y_;

	void GenerateCharMesh(char c);
};

