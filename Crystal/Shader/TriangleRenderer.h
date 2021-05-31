#pragma once

#include "ShaderObject.h"
#include "GLObjectFactory.h"
#include "VertexBufferObject.h"
#include "ShaderBuildStatus.h"

namespace Crystal {
	namespace Shader {

class TriangleRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		std::vector<unsigned int> indices;
	};

	TriangleRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& glFactory);

	void release(Shader::GLObjectFactory& glFactory);

	//void setScene(TriangleShaderScene* scene) { this->scene = scene; }

	void render(const Buffer& buffer);

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}