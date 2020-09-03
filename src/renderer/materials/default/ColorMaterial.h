#pragma once

#include <glm/glm.hpp>
#include "../Material.h"

class ColorMaterial: public Material
{
public:
	ColorMaterial(Shader *shader);

	void Bind();
	void Unbind();

	void SetColor(glm::vec3 color);

private:
	glm::vec4 color_;
};

