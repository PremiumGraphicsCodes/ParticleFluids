#include "VertexArrayObject.h"

using namespace Crystal::Shader;

void VertexArrayObject::build()
{
	glGenVertexArrays(1, &handle);
}

void VertexArrayObject::bind()
{
	glBindVertexArray(handle);
}

void VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}
