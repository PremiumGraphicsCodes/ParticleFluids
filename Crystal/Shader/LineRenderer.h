#pragma once

#include "VertexBufferObject.h"

#include "../Shader/GLObjectFactory.h"
#include "../Math/Matrix4d.h"
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Shader {

class LineRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* color;
		std::vector<unsigned int> indices;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelViewMatrix;
		GLfloat lineWidth;
	};
	//Shader::VertexArrayObject vao;

	LineRenderer();

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void render(const Buffer& buffer);

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	Shader::ShaderObject* shader;
};

	}
}