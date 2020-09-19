#pragma once

#include <vector>
#include "Shader.h"

class ShaderManager
{
public:
	static ShaderManager &GetInstance();

	void Add(Shader *shader);
	Shader *Get(const char *name);
	void Remove(const char *name);

	ShaderManager(const ShaderManager &) = delete;
	void operator=(const ShaderManager &) = delete;

private:
	ShaderManager();
	~ShaderManager();

	std::vector<Shader *> shaders_;
};

