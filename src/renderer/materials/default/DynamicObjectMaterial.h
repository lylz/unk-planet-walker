#pragma once

#include <glm/glm.hpp>
#include "../Material.h"

class DynamicObjectMaterial: public Material
{
public:
	DynamicObjectMaterial(Shader *shader, Texture *texture);

	void Bind();
	void Unbind();

	glm::mat4 model_matrix();
	glm::mat4 view_matrix();
	glm::mat4 projection_matrix();

	void SetModelMatrix(glm::mat4 model_matrix);
	void SetViewMatrix(glm::mat4 view_matrix);
	void SetProjectionMatrix(glm::mat4 projection_matrix);

private:
	glm::mat4 model_matrix_;
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;

	unsigned int texture_slot_;
};