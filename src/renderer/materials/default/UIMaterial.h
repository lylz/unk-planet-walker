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

private:
	glm::mat4 orthographic_matrix_;
};

