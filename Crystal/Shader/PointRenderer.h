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
	};

	PointRenderer();

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void send(const Buffer& buffer);

	void render(const Graphics::Camera& camera, const int count);

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject shader;

	int count;
};

	}
}