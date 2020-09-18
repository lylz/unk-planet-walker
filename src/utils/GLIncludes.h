#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

extern void GLErrorCheck(const char *function, const char *file, int line);

#ifdef _DEBUG
	#define GLWCall(x) \
		x; \
		GLErrorCheck(#x, __FILE__, __LINE__);
#else
	#define GLWCall(x) x
#endif
