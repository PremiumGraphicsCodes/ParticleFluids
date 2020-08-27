#pragma once

#include "LineShader.h"
#include "TriangleShaderScene.h"

namespace Crystal {
	namespace Scene {

class TriangleShader
{
public:

	TriangleShader(const std::string& name);

	bool build();

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