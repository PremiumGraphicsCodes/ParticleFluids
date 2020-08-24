#pragma once

#include "LineShader.h"
#include "TriangleShaderScene.h"

namespace Crystal {
	namespace Scene {

class TriangleShader
{
public:

	TriangleShader();

	bool build();

	void setBuffer(const TriangleShaderScene& glBuffer) { this->glBuffer = glBuffer; }

	void render(const Graphics::Camera& camera);

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	TriangleShaderScene glBuffer;
	Shader::ShaderObject shader;
};

	}
}