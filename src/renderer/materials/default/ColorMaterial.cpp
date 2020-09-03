#include "ColorMaterial.h"

ColorMaterial::ColorMaterial(Shader *shader)
	: Material(shader)
{
	color_ = glm::vec4(0.7, 0.5, 0.3, 1.0);
}

void ColorMaterial::Bind()
{
	shader_->Use();

	shader_->SetUniform("inColor", color_);
}

void ColorMaterial::Unbind()
{
	// TODO: unbind shader via glUseProgram(0)
}

void ColorMaterial::SetColor(glm::vec3 color)
{
	color_ = glm::vec4(color, 1.0f);
}
