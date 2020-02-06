#pragma once

#include <vector>
#include "glew.h"

namespace Crystal {
	namespace Shader {

class VertexBufferObject
{
public:
	VertexBufferObject();

	~VertexBufferObject();

	void build();

	void release();

	void send(const std::vector<float>& values);

	GLuint getHandle() const { return handle; }

	void bind() const;

	void unbind() const;

private:
	GLuint handle;
};

	}
}
