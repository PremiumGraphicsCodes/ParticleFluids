#pragma once

#include "glew.h"

namespace Crystal {
	namespace Shader {

class VertexArrayObject
{
public:
	void build();

	void bind();

	void unbind();

private:
	GLuint handle;

};
	}
}