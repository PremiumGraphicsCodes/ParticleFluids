#include "LineShader.h"
#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr const char* positionLabel = "position";
	constexpr const char* colorLabel = "color";
	constexpr const char* projectionMatrixLabel = "projectionMatrix";
	constexpr const char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr const char* fragColorLabel = "fragColor";
}

LineShader::LineShader()
{
}

bool LineShader::build(GLObjectFactory& factory)
{
	const auto& vsSource = getBuiltInVsSource();
	const auto& fsSource = getBuiltInFsSource();
	const auto isOk = shader.build(vsSource, fsSource);

	shader.findUniformLocation(::projectionMatrixLabel);
	shader.findUniformLocation(::modelViewMatrixLabel);

	shader.findAttribLocation(::positionLabel);
	shader.findAttribLocation(::colorLabel);

	return isOk;
}

void LineShader::release()
{
	shader.release();
}

void LineShader::render()
{
	const auto& projectionMatrix = glBuffer.camera.getProjectionMatrix();
	const auto& modelviewMatrix = glBuffer.camera.getModelViewMatrix() * glBuffer.matrix;

	shader.bind();

	shader.setLineWidth(glBuffer.lineWidth);
	shader.enableDepthTest();

	shader.sendUniform(projectionMatrixLabel, projectionMatrix);
	shader.sendUniform(modelViewMatrixLabel, modelviewMatrix);

	shader.sendVertexAttribute3df(positionLabel, glBuffer.vbo.position);
	shader.sendVertexAttribute4df(colorLabel, glBuffer.vbo.color);

	shader.drawLines(glBuffer.indices);

	//shader->disableVertexAttribute("color");
	//shader->disableVertexAttribute("position");

	shader.bindOutput(::fragColorLabel);

	shader.setLineWidth(1);
	shader.disableDepthTest();

	shader.unbind();

	assert(GL_NO_ERROR == glGetError());
}

std::string LineShader::getBuiltInVsSource() const
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

std::string LineShader::getBuiltInFsSource() const
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