#include "GLIncludes.h"
#include <iostream>
#include <string>

void GLErrorCheck(const char *function, const char *file, int line)
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::string function_name = function;
		std::string file_name = file;
		std::string error_number = std::to_string(error);
		throw std::runtime_error("ERROR: " + error_number + " in " + function_name + " in file " + file_name + " line " + std::to_string(line));
	}
}