#pragma once

#include "PointBuffer.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"

namespace Crystal {
	namespace Scene {

struct PointShaderBuffer
{
	struct VBO
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject size;
		Shader::VertexBufferObject color;
	};

	//Shader::VertexArrayObject vao;
	VBO vbo;
	GLuint count;
	Math::Matrix4df matrix;

	void build();

	void release();

	void send(const PointBuffer& buffer);
};

	}
}