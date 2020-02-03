#pragma once

#include <vector>
#include "glew.h"

namespace Crystal {
	namespace Shader {

class VertexBufferObject
{
public:
	void build();

	void send(const std::vector<float>& values);

	GLuint getHandle() const { return handle; }

	void bind();

	void unbind();

private:
	GLuint handle;
};

	}
}
