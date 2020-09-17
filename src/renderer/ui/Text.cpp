#include "Text.h"
#include "../materials/default/TextureHolderMaterial.h"

Text::Text(std::string text, Font font)
	: text_(text), font_(font)
{
	font_atlas_texture_ = new Texture(font_.atlas_path.c_str());
	material_ = new TextureHolderMaterial(font_atlas_texture_);

	x_ = 0;
	y_ = 0;
	
	for (auto c : text_)
	{
		GenerateCharMesh(c);
	}
}

Text::~Text()
{
	meshes_.clear();
}

void Text::GenerateCharMesh(char c)
{
	Vertex v1, v2, v3, v4;
	GlyphInfo glyph = font_.glyphs[c];

	// TODO: take framebuffer width and height from outside
	float char_x_scale = 0.05; // 2.0f / 1024.0f;
	float char_y_scale = 0.05; // 2.0f / 720.0f;

	float xpos = x_ + (glyph.bearing.x * char_x_scale);
	float ypos = y_ - (glyph.size.y - glyph.bearing.y) * char_y_scale;

	float uv_n_factor = 1.0f / font_.atlas_size.x; // uv normalization factor. for now assuming that texture is a square (which is true considering current FontLoader)

	v1.position.x = xpos;
	v1.position.y = ypos;
	v1.position.z = 0;
	v1.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v1.uv.x = glyph.x0 * uv_n_factor;
	v1.uv.y = glyph.y1 * uv_n_factor;

	v2.position.x = xpos;
	v2.position.y = ypos + glyph.size.y * char_y_scale;
	v2.position.z = 0;
	v2.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v2.uv.x = glyph.x0 * uv_n_factor;
	v2.uv.y = glyph.y0 * uv_n_factor;

	v3.position.x = xpos + glyph.size.x * char_x_scale;
	v3.position.y = ypos + glyph.size.y * char_y_scale;
	v3.position.z = 0;
	v3.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v3.uv.x = glyph.x1 * uv_n_factor;
	v3.uv.y = glyph.y0 * uv_n_factor;

	v4.position.x = xpos + glyph.size.x * char_x_scale;
	v4.position.y = ypos;
	v4.position.z = 0;
	v4.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v4.uv.x = glyph.x1 * uv_n_factor;
	v4.uv.y = glyph.y1 * uv_n_factor;

	x_ += glyph.advance * char_x_scale;

	meshes_.push_back(new Mesh({ v1, v2, v3, v4 }, { 0, 1, 2, 2, 3, 0 }, material_));
}

std::vector<Mesh *> Text::meshes()
{
	return meshes_;
}
