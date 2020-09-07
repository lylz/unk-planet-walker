#include "UIMaterial.h"

UIMaterial::UIMaterial(Shader *shader)
	: BatchMaterial(shader)
{};

void UIMaterial::Bind()
{
	shader_->Use();

	std::vector<float> texture_slots;

	for (size_t i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];

		texture->Bind();
		texture_slots.push_back(texture->slot());
	}

	shader_->SetUniform("u_Textures", texture_slots.data(), texture_slots.size());
}

void UIMaterial::Unbind()
{
	for (size_t i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];

		texture->Unbind();
	}
}
