#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../BatchMaterial.h"

class UIMaterial: public BatchMaterial
{
public:
	UIMaterial(Shader *shader);

	void Bind();
	void Unbind();

	void SetViewMatrix(glm::mat4 view_matrix);
	void SetProjectionMatrix(glm::mat4 projection_matrix);

private:
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;
};

