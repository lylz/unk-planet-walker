#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include "../../utils/GLIncludes.h"

class ShaderException : public std::runtime_error
{
public:
	ShaderException(const std::string &msg) :
		std::runtime_error(msg) {};
};

enum ShaderType
{
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	TESS_CONTROL = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	COMPUTE = GL_COMPUTE_SHADER
};

class Shader
{
private:
	int handle_;
	bool linked_;
	std::map<std::string, int> uniform_locations_;

	GLint GetUniformLocation(const char *name);
	bool FileExists(const char *name);
	std::string GetExtension(const char *name);
	void ThrowShaderProgramError(std::string message);

public:
	Shader();
	~Shader();

	void CompileShader(const char *filename);
	void CompileShader(const char *filename, ShaderType type);
	void CompileShader(const std::string &source, ShaderType type, const char *filename = NULL);

	void Link();
	void Use();
	void Validate();

	int handle();
	bool linked();

	void BindAttribLocation(GLuint location, const char *name);
	void BindFragDataLocation(GLuint location, const char *name);

	void SetUniform(const char *name, float x, float y, float z);
	void SetUniform(const char *name, const glm::vec2 &v);
	void SetUniform(const char *name, const glm::vec3 &v);
	void SetUniform(const char *name, const glm::vec4 &v);
	void SetUniform(const char *name, const glm::mat4 &m);
	void SetUniform(const char *name, const glm::mat3 &m);
	void SetUniform(const char *name, float val);
	void SetUniform(const char *name, int val);
	void SetUniform(const char *name, bool val);

	static Shader *CreateFromFiles(const char *vertex_shader, const char *fragment_shader);
};
