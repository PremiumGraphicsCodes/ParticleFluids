#pragma once

#include "PointBuffer.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/VertexArrayObject.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Scene {

class PointShaderBuffer
{
public:
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
	Graphics::Camera camera;

	void build();

	void release();

	void send(const PointBuffer& buffer);
};

	}
}