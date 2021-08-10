#include "UIButtonMaterial.h"
#include <glm/gtc/matrix_transform.hpp>

UIButtonMaterial::UIButtonMaterial(Shader *shader)
    :Material(shader, nullptr)
{
    // TODO: get width and height from ApplicationSettings
	orthographic_matrix_ = glm::ortho(0.0f, 720.0f, 1024.0f, 0.0f, -1.0f, 1.0f);
    color_ = { 255, 255, 255, 1 };
}

void UIButtonMaterial::Bind()
{
    shader_->Use();
    shader_->SetUniform("u_Ortho", orthographic_matrix_);
    shader_->SetUniform("u_Color", color_);
}

void UIButtonMaterial::Unbind()
{
}

void UIButtonMaterial::ChangeColor(glm::vec4 color)
{
    color_ = color;
}
