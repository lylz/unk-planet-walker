#include "Shader.h"

#include <fstream>
#include <sstream>
#include <sys/stat.h>

using std::ifstream;
using std::ios;

struct ShaderFileExtension {
	const char *ext;
	ShaderType type;
};

struct ShaderFileExtension extensions[] =
{
	{".vs",		ShaderType::VERTEX},
	{".vert",	ShaderType::VERTEX},
	{".gs",		ShaderType::GEOMETRY},
	{".geom",	ShaderType::GEOMETRY},
	{".tcs",	ShaderType::TESS_CONTROL},
	{".tes",	ShaderType::TESS_CONTROL},
	{".fs",		ShaderType::FRAGMENT},
	{".frag",	ShaderType::FRAGMENT},
	{".cs",		ShaderType::COMPUTE}
};

Shader::Shader(const char *name) : Resource(name), handle_(0), linked_(false) { }

Shader::~Shader() {
	if (handle_ == 0)
	{
		return;
	}

	// Query the number of attached shaders
	GLint shaders_amount = 0;
	glGetProgramiv(handle_, GL_ATTACHED_SHADERS, &shaders_amount);

	// Get the shader names
	GLuint *shader_names = new GLuint[shaders_amount];
	glGetAttachedShaders(handle_, shaders_amount, NULL, shader_names);

	// Delete the program
	glDeleteProgram(handle_);

	delete[] shader_names;
}

std::string Shader::GetExtension(const char *name) {
	std::string name_string(name);

	size_t dot_location = name_string.find_last_of('.');

	if (dot_location != std::string::npos)
	{
		return name_string.substr(dot_location, std::string::npos);
	}

	return "";
}

bool Shader::FileExists(const char *name)
{
	struct stat info;

	return stat(name, &info) == 0;
}

void Shader::CompileShader(const char *filename)
{
	int extensions_amount = sizeof(extensions) / sizeof(ShaderFileExtension);

	std::string extension = GetExtension(filename);
	ShaderType type = ShaderType::VERTEX;
	bool match_found = false;

	for (int i = 0; i < extensions_amount; i++)
	{
		if (extension == extensions[i].ext)
		{
			match_found = true;
			type = extensions[i].type;
			break;
		}
	}

	if (!match_found)
	{
		std::string msg = "Unrecognized extension: " + extension;
		throw ShaderException(msg);
	}

	this->CompileShader(filename, type);
}

void Shader::CompileShader(const char *filename, ShaderType type)
{
	if (!this->FileExists(filename))
	{
		std::string msg = "Shader: " + std::string(filename) + " not found";
		throw ShaderException(msg);
	}

	if (this->handle_ <= 0)
	{
		this->handle_ = glCreateProgram();

		if (this->handle_ == 0)
		{
			throw ShaderException("Unable to create shader program.");
		}
	}

	ifstream file(filename, ios::in);

	if (!file)
	{
		std::string msg = "Unable to open: " + std::string(filename);
		throw ShaderException(msg);
	}

	std::stringstream code;
	code << file.rdbuf();
	file.close();

	this->CompileShader(code.str(), type, filename);
}

void Shader::CompileShader(const std::string &source, ShaderType type, const char *filename)
{
	if (this->handle_ <= 0)
	{
		this->handle_ = glCreateProgram();

		if (this->handle_ == 0)
		{
			throw ShaderException("Unable to create shader program.");
		}
	}

	GLint shader_handle = glCreateShader(type);
	const char *c_code = source.c_str();

	glShaderSource(shader_handle, 1, &c_code, NULL);
	glCompileShader(shader_handle);

	GLint result;
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &result);

	if (GL_FALSE == result)
	{
		std::string log_string, msg;

		GLint log_length;
		glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_length);

		if (log_length > 0)
		{
			char *c_log = new char[log_length];

			GLsizei written;
			glGetShaderInfoLog(shader_handle, log_length, &written, c_log);

			log_string = c_log;

			delete[] c_log;
		}

		if (filename)
		{
			msg = std::string(filename) + ": shader compilation failed!\n";
		}
		else
		{
			msg = "Shader compilation failed!\n";
		}

		msg += log_string;
		throw ShaderException(msg);
	}
	else
	{
		glAttachShader(this->handle_, shader_handle);
	}
}

void Shader::Link()
{
	if (this->linked_)
	{
		return;
	}

	if (this->handle_ <= 0)
	{
		throw ShaderException("Program has not been compiled.");
	}

	glLinkProgram(this->handle_);

	int status = 0;

	glGetProgramiv(this->handle_, GL_LINK_STATUS, &status);

	if (GL_FALSE == status)
	{
		ThrowShaderProgramError("Program link failed:\n");
	}
	else
	{
		uniform_locations_.clear();
		linked_ = true;
	}
}

void Shader::Use()
{
	if (this->handle_ <= 0 || !this->linked_)
	{
		throw ShaderException("Shader has not been linked.");
	}

	glUseProgram(this->handle_);
}

void Shader::Validate()
{
	if (!this->linked_)
	{
		throw ShaderException("Program is not linked.");
	}

	GLint status;

	glValidateProgram(this->handle_);
	glGetProgramiv(this->handle_, GL_VALIDATE_STATUS, &status);

	if (GL_FALSE == status)
	{
		ThrowShaderProgramError("Program failed to validate\n");
	}
}

int Shader::handle()
{
	return this->handle_;
}

bool Shader::linked()
{
	return this->linked_;
}

void Shader::BindAttribLocation(GLuint location, const char *name)
{
	glBindAttribLocation(this->handle_, location, name);
}

void Shader::BindFragDataLocation(GLuint location, const char *name)
{
	glBindFragDataLocation(this->handle_, location, name);
}

int Shader::GetUniformLocation(const char *name)
{
	std::map<std::string, int>::iterator pos;
	pos = uniform_locations_.find(name);

	if (pos == uniform_locations_.end())
	{
		uniform_locations_[name] = glGetUniformLocation(this->handle_, name);
	}

	return uniform_locations_[name];
}

void Shader::SetUniform(const char *name, float x, float y, float z)
{
	GLint location = this->GetUniformLocation(name);
	glUniform3f(location, x, y, z);
}

void Shader::SetUniform(const char *name, const glm::vec2 &v)
{
	GLint location = this->GetUniformLocation(name);
	glUniform2f(location, v.x, v.y);
}

void Shader::SetUniform(const char *name, const glm::vec3 &v)
{
	this->SetUniform(name, v.x, v.y, v.z);
}

void Shader::SetUniform(const char *name, const glm::vec4 &v)
{
	GLint location = this->GetUniformLocation(name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::SetUniform(const char *name, const glm::mat3 &m)
{
	GLint location = this->GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniform(const char *name, const glm::mat4 &m)
{
	GLint location = this->GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniform(const char *name, int *arr, unsigned int size)
{
	GLint location = this->GetUniformLocation(name);
	glUniform1iv(location, size, arr);
}

void Shader::SetUniform(const char *name, float val)
{
	GLint location = this->GetUniformLocation(name);
	glUniform1f(location, val);
}

void Shader::SetUniform(const char *name, int val)
{
	GLint location = this->GetUniformLocation(name);
	glUniform1i(location, val);
}

void Shader::SetUniform(const char *name, bool val)
{
	GLint location = this->GetUniformLocation(name);
	glUniform1i(location, val);
}

void Shader::ThrowShaderProgramError(std::string message)
{
	int log_length = 0;
	std::string log_string;

	glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length > 0)
	{
		char *c_log = new char[log_length];
		int written = 0;

		glGetProgramInfoLog(handle_, log_length, &written, c_log);

		log_string = c_log;
		delete[] c_log;
	}

	throw ShaderException(message + log_string);
}

Shader* Shader::CreateFromFiles(const char *name, const char *vertex_shader, const char *fragment_shader)
{
	Shader *shader = new Shader(name);

	shader->CompileShader(vertex_shader);
	shader->CompileShader(fragment_shader);
	shader->Link();
	shader->Validate();

	return shader;
}