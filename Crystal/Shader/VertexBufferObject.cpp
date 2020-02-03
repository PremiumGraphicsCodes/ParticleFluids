#include "VertexBufferObject.h"

#include "glew.h"

using namespace Crystal::Shader;

void VertexBufferObject::build()
{
	glGenBuffers(1, &handle);
}

void VertexBufferObject::send(const std::vector<float>& values)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(values[0]) * values.size(), values.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VertexBufferObject::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

