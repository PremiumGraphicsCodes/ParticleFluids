#include "TriangleShader.h"

#include <sstream>

#include "../Shader/VertexBufferObject.h"


using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

namespace {
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelViewMatrixLabel = "modelviewMatrix";
}

void TriangleShaderScene::build()
{
	vbo.position.build();
	vbo.color.build();
}

void TriangleShaderScene::release()
{
	vbo.position.release();
	vbo.color.release();
}

void TriangleShaderScene::send(const LineBuffer& buffer)
{
	vbo.position.send(buffer.getPositions().get());
	vbo.color.send(buffer.getColors().get());

	indices = buffer.getIndices().get();
}

TriangleShader::TriangleShader()
{
}

bool TriangleShader::build()
{
	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	const auto isOk = shader.build(vsSource, fsSource);

	shader.findUniformLocation(::projectionMatrixLabel);
	shader.findUniformLocation(::modelViewMatrixLabel);

	shader.findAttribLocation("position");
	shader.findAttribLocation("color");

	return isOk;
}

void TriangleShader::render(const Camera& camera)
{
	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix();

	shader.bind();
	shader.bindOutput("fragColor");

	shader.enableDepthTest();

	shader.sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader.sendUniform(::modelViewMatrixLabel, modelviewMatrix);

	shader.sendVertexAttribute3df("position", glBuffer.vbo.position);
	shader.sendVertexAttribute4df("color", glBuffer.vbo.color);

	shader.enableVertexAttribute("position");
	shader.enableVertexAttribute("color");

	shader.drawTriangles(glBuffer.indices);

	shader.disableVertexAttribute("color");
	shader.disableVertexAttribute("position");

	shader.disableDepthTest();

	shader.unbind();
}

std::string TriangleShader::getBuildInVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vColor = color;" << std::endl
		<< "}";
	return stream.str();

}

std::string TriangleShader::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = vColor;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}
