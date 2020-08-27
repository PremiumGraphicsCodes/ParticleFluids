#include "TriangleShader.h"

#include <sstream>

#include "../Shader/VertexBufferObject.h"
#include "CameraShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

namespace {
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelViewMatrixLabel = "modelviewMatrix";
}

TriangleShader::TriangleShader(const std::string& name) :
	IShaderScene(name)
{
}

bool TriangleShader::build(GLObjectFactory& factory)
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

void TriangleShader::release(GLObjectFactory& glFactory)
{

}


void TriangleShader::render()
{
	const auto& projectionMatrix = scene->getCamera()->getProjectionMatrix();
	const auto& modelviewMatrix = scene->getCamera()->getModelViewMatrix();

	shader.bind();
	shader.bindOutput("fragColor");

	shader.enableDepthTest();

	shader.sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader.sendUniform(::modelViewMatrixLabel, modelviewMatrix);

	shader.sendVertexAttribute3df("position", scene->vbo.position);
	shader.sendVertexAttribute4df("color", scene->vbo.color);

	shader.enableVertexAttribute("position");
	shader.enableVertexAttribute("color");

	shader.drawTriangles(scene->indices);

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
