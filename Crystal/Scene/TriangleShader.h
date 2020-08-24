#pragma once

#include "LineShader.h"

#include "../Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Scene {

class TriangleShaderScene
{
public:
	struct VBO {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
	};
	VBO vbo;
	std::vector<unsigned int> indices;

	void build();

	void release();

	void send(const LineBuffer& buffer);
};


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