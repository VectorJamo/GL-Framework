#pragma once
#include <GL/glew.h>

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLGetError()
{
	if (int error = glGetError())
	{
		std::cout << "|| OpenGL Error : ||" << "(Error Code): " << error << " (Line no): " << __LINE__ << std::endl; 
		return true;
	}
	return false;
}
#define ASSERT(x) if(x) __debugbreak();
#ifdef DEBUG 
	#define GLCall(x) GLClearError(); x; ASSERT(GLGetError())
#else
	#define GLCall(x) x
#endif

