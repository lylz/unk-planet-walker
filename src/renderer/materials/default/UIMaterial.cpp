#include "UIMaterial.h"
#include <glm/gtc/matrix_transform.hpp>

UIMaterial::UIMaterial(Shader *shader)
	: BatchMaterial(shader)
{
    // TODO: get width and height from ApplicationSettings
	orthographic_matrix_ = glm::ortho(0.0f, 720.0f, 1024.0f, 0.0f, -1.0f, 1.0f);
};

void UIMaterial::Bind()
{
	shader_->Use();

	std::vector<int> texture_slots;

	for (size_t i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];
		unsigned int texture_slot = textures_slots_map_.find(texture->id())->second;

		texture->Bind(texture_slot);
		texture_slots.push_back(texture_slot);
	}

	shader_->SetUniform("u_Textures", texture_slots.data(), texture_slots.size());
	shader_->SetUniform("u_Ortho", orthographic_matrix_);
}

void UIMaterial::Unbind()
{
	for (size_t i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];

		texture->Unbind(i);
	}
}
