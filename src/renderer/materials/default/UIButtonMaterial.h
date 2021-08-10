#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../Material.h"

class UIButtonMaterial: public Material
{
public:
	UIButtonMaterial(Shader *shader);

	void Bind();
	void Unbind();
    void ChangeColor(glm::vec4 color);

private:
	glm::mat4 orthographic_matrix_;
    glm::vec4 color_;
};

