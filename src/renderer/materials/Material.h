#pragma once

#include "../shaders/Shader.h"

class Material
{
public:
	Material(Shader *shader) : shader_(shader) {};

protected:
	Shader *shader_;

public:
	inline Shader *shader() { return shader_; };

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

};

