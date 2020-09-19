#pragma once

#include <glm/glm.hpp>
#include "../BatchMaterial.h"

class StaticObjectsMaterial: public BatchMaterial
{
public:
	StaticObjectsMaterial(Shader *shader);

	void Bind();
	void Unbind();

	void SetViewMatrix(glm::mat4 view_matrix);
	void SetProjectionMatrix(glm::mat4 projection_matrix_);

private:
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;
};

