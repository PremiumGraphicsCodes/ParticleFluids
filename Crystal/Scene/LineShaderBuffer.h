#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"

#include "../Shader/VertexBufferObject.h"
#include "../Graphics/Camera.h"

#include "LineBuffer.h"

namespace Crystal {
	namespace Scene {

class LineShaderBuffer
{
public:
	struct {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
	} vbo;
	//Shader::VertexArrayObject vao;

	std::vector<unsigned int> indices;
	Math::Matrix4df matrix;
	Graphics::Camera camera;
	float lineWidth;

	void build();

	void release();

	void send(const LineBuffer& buffer);
};

	}
}