#pragma once

#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "GLObjectFactory.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Shader {

class PointRenderer// : public IShaderScene
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject size;
		Shader::VertexBufferObject color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		const int count;
	};

	PointRenderer();

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void render(const Buffer& buffer);

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject shader;
};

	}
}