#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


//Insertion function
#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLOGCall(#x, __FILE__ , __LINE__))

bool GLLOGCall(const char* function, const char* file, int line);

void GLClearError();

void GLCheckError();

class Renderer
{
public:
	void Clear() const;

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};