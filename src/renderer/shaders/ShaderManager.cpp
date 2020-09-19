#include "ShaderManager.h"

ShaderManager::ShaderManager()
{}

ShaderManager &ShaderManager::GetInstance()
{
	static ShaderManager instance;

	return instance;
}

ShaderManager::~ShaderManager()
{
	for (unsigned int i = 0; i < shaders_.size(); i++)
	{
		delete shaders_[i];
	}
}

void ShaderManager::Add(Shader *shader)
{
	shaders_.push_back(shader);
}

Shader *ShaderManager::Get(const char *name)
{
	for (Shader *shader : shaders_)
	{
		if (shader->name() == name)
		{
			return shader;
		}
	}

	return nullptr;
}

void ShaderManager::Remove(const char *name)
{
	for (unsigned int i = 0; i < shaders_.size(); i++)
	{
		Shader *shader = shaders_[i];

		if (shader->name() == name)
		{
			delete shader;
			shaders_.erase(shaders_.begin() + i);
			return;
		}
	}
}

