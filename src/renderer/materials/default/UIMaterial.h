#pragma once

#include <vector>
#include "../BatchMaterial.h"

class UIMaterial: public BatchMaterial
{
public:
	UIMaterial(Shader *shader);

	void Bind();
	void Unbind();
};

