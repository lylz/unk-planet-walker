#include "StaticObjectsMaterial.h"
#include <glm/gtc/matrix_transform.hpp>

StaticObjectsMaterial::StaticObjectsMaterial(Shader *shader)
	: BatchMaterial(shader)
{
	view_matrix_ = glm::mat4(1);
	projection_matrix_ = glm::mat4(1);
};

void StaticObjectsMaterial::Bind()
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
	shader_->SetUniform("u_View", view_matrix_);
	shader_->SetUniform("u_Proj", projection_matrix_);
}

void StaticObjectsMaterial::Unbind()
{
	for (size_t i = 0; i < textures_.size(); i++)
	{
		Texture *texture = textures_[i];

		texture->Unbind(i);
	}
}

void StaticObjectsMaterial::SetViewMatrix(glm::mat4 view_matrix)
{
	view_matrix_ = view_matrix;
}

void StaticObjectsMaterial::SetProjectionMatrix(glm::mat4 projection_matrix)
{
	projection_matrix_ = projection_matrix;
}

