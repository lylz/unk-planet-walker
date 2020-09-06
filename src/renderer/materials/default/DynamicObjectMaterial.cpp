#include "DynamicObjectMaterial.h"

DynamicObjectMaterial::DynamicObjectMaterial(Shader *shader, Texture *texture)
	: Material(shader, texture)
{
	model_matrix_ = glm::mat4(1.0f);
	view_matrix_ = glm::mat4(1.0f);
	projection_matrix_ = glm::mat4(1.0f);
}

void DynamicObjectMaterial::Bind()
{
	shader_->Use();

	shader_->SetUniform("u_Model", model_matrix_);
	shader_->SetUniform("u_View", view_matrix_);
	shader_->SetUniform("u_Proj", projection_matrix_);

	if (texture_ != nullptr)
	{
		texture_->Bind();
		shader_->SetUniform("u_Texture", (int) texture_->slot());
	}
}

void DynamicObjectMaterial::Unbind()
{
	if (texture_ != nullptr)
	{
		texture_->Unbind();
	}
	// TODO: unbind shader via glUseProgram(0)
}

glm::mat4 DynamicObjectMaterial::model_matrix()
{
	return model_matrix_;
}

glm::mat4 DynamicObjectMaterial::view_matrix()
{
	return view_matrix_;
}

glm::mat4 DynamicObjectMaterial::projection_matrix()
{
	return projection_matrix_;
}

void DynamicObjectMaterial::SetModelMatrix(glm::mat4 model_matrix)
{
	model_matrix_ = model_matrix;
}

void DynamicObjectMaterial::SetViewMatrix(glm::mat4 view_matrix)
{
	view_matrix_ = view_matrix;
}

void DynamicObjectMaterial::SetProjectionMatrix(glm::mat4 projection_matrix)
{
	projection_matrix_ = projection_matrix;
}
