#pragma once

#include "LineShader.h"
#include "TriangleShaderScene.h"

namespace Crystal {
	namespace Scene {

class TriangleShader : public IShaderScene
{
public:
	explicit TriangleShader(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory);

	void release(Shader::GLObjectFactory& glFactory);

	void setScene(TriangleShaderScene* scene) { this->scene = scene; }

	void render();

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject shader;
	TriangleShaderScene* scene;
};

	}
}