#include "UIMaterial.h"

UIMaterial::UIMaterial(Shader *shader)
	: BatchMaterial(shader)
{
	view_matrix_ = glm::mat4(1.0f);
	projection_matrix_ = glm::mat4(1.0f);
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

	shader_->SetUniform("u_Proj", projection_matrix_);
	shader_->SetUniform("u_View", view_matrix_);
}

void UIMaterial::Unbind()
{
	for (size_t i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];

		texture->Unbind(i);
	}
}

void UIMaterial::SetViewMatrix(glm::mat4 view_matrix)
{
	view_matrix_ = view_matrix;
}

void UIMaterial::SetProjectionMatrix(glm::mat4 projection_matrix)
{
	projection_matrix_ = projection_matrix;
}
