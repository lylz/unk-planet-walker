#pragma once

#include "../shaders/Shader.h"
#include "../Texture.h"

class Material
{
public:
	Material(Shader *shader, Texture *texture) : shader_(shader), texture_(texture) {};

protected:
	Shader *shader_;
	Texture *texture_;

public:
	inline Shader *shader() { return shader_; };
	inline Texture *texture() { return texture_; };

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

};

