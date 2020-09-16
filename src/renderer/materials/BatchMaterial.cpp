#include "BatchMaterial.h"

BatchMaterial::BatchMaterial(Shader *shader)
	: Material(shader, nullptr)
{}

void BatchMaterial::AddTexture(Texture *texture, unsigned int slot)
{
	textures_.push_back(texture);
	textures_slots_map_.insert({ texture->id(), slot });
}

void BatchMaterial::FlushTextures()
{
	textures_slots_map_.clear();
	textures_.clear();
}