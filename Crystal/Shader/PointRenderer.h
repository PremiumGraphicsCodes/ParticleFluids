#pragma once

#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "GLObjectFactory.h"
#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"
#include "ShaderBuildStatus.h"
#include <string>

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
		int count = 0;
	};

	PointRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void render(const Buffer& buffer);

	void renderBlend(const Buffer& buffer);

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}