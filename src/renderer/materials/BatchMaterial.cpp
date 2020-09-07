#include "BatchMaterial.h"

BatchMaterial::BatchMaterial(Shader *shader)
	: Material(shader, nullptr)
{}

void BatchMaterial::AddTexture(Texture *texture)
{
	textures_.push_back(texture);
}

void BatchMaterial::FlushTextures()
{
	textures_.clear();
}