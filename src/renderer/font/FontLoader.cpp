#include "FontLoader.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <sys/stat.h>
#include <iostream>

Font FontLoader::Load(std::string file_path)
{
    struct stat file_info;

    if (stat(file_path.c_str(), &file_info) != 0)
    {
        throw std::runtime_error("ERROR: unable to open font file.\n");
    }

    Font font;
	FT_Library ft;
	FT_Face face;

	float char_height = 16 << 6;
	FT_Init_FreeType(&ft);
	FT_New_Face(ft, file_path.c_str(), 0, &face);
    FT_Set_Char_Size(face, 0, char_height, 96, 96); // TODO: use user-defined char config

	font.size = face->size->metrics.height >> 6;
	int max_dimention = (1 + font.size) * ceilf(sqrtf(GLYPHS_COUNT));
	int texture_width = 1;

	while (texture_width < max_dimention)
	{
		texture_width <<= 1;
	}

	int texture_height = texture_width;

	char *pixels = (char*) calloc(texture_width * texture_height, 1);
	int pen_x = 0, pen_y = 0;

    for (int i = 0; i < GLYPHS_COUNT; ++i)
    {
        FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
        FT_Bitmap *bitmap = &face->glyph->bitmap;

        if (pen_x + bitmap->width >= texture_width)
        {
            pen_x = 0;
            pen_y += ((face->size->metrics.height >> 6) + 1);
        }

        for (int row = 0; row < bitmap->rows; ++row)
        {
            for (int col = 0; col < bitmap->width; ++col)
            {
                int x = pen_x + col;
                int y = pen_y + row;

                pixels[y * texture_width + x] = bitmap->buffer[row * bitmap->pitch + col];
            }
        }

        GlyphInfo glyph = {};

        glyph.x0 = pen_x;
        glyph.y0 = pen_y;
        glyph.x1 = pen_x + bitmap->width;
        glyph.y1 = pen_y + bitmap->rows;
        glyph.size.x = bitmap->width;
        glyph.size.y = bitmap->rows;
        glyph.bearing.x = face->glyph->bitmap_left;
        glyph.bearing.y = face->glyph->bitmap_top;
        glyph.advance = face->glyph->advance.x >> 6;

        font.glyphs[i] = glyph;

        pen_x += bitmap->width + 1;
    }

    FT_Done_FreeType(ft);

    char *atlas_data = (char *)calloc(texture_width * texture_height * 4, 1);

    for (int i = 0; i < (texture_width * texture_height); ++i)
    {
        atlas_data[i * 4 + 0] |= pixels[i];
        atlas_data[i * 4 + 1] |= pixels[i];
        atlas_data[i * 4 + 2] |= pixels[i];
        atlas_data[i * 4 + 3] |= 0xff;
    }

    std::string atlas_path = "assets/fonts/.font_atlas.png";

    // TODO: handle possible errors with file write
    stbi_write_png(atlas_path.c_str(), texture_width, texture_height, 4, atlas_data, texture_width * 4);

    font.atlas_path = atlas_path;
    font.atlas_size = glm::ivec2(texture_width, texture_height);

    free(atlas_data);
    free(pixels);

    return font;
}
