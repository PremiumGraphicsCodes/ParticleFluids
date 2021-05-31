#include "LineRenderer.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr const char* positionLabel = "position";
	constexpr const char* colorLabel = "color";
	constexpr const char* projectionMatrixLabel = "projectionMatrix";
	constexpr const char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr const char* fragColorLabel = "fragColor";
}

LineRenderer::LineRenderer()
{
}

ShaderBuildStatus LineRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	const auto& vsSource = getBuiltInVsSource();
	const auto& fsSource = getBuiltInFsSource();

	this->shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	status.isOk = true;

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);

	return status;
}

void LineRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void LineRenderer::render(const Buffer& buffer)
{
	if (buffer.indices.empty()) {
		return;
	}
	shader->bind();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->setLineWidth(buffer.lineWidth);
	shader->enableDepthTest();

	shader->sendVertexAttribute3df(positionLabel, *buffer.position);
	shader->sendVertexAttribute4df(colorLabel, *buffer.color);

	shader->drawLines(buffer.indices);

	//shader->disableVertexAttribute("color");
	//shader->disableVertexAttribute("position");

	shader->bindOutput(::fragColorLabel);

	shader->setLineWidth(1);
	shader->disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}

std::string LineRenderer::getBuiltInVsSource() const
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

std::string LineRenderer::getBuiltInFsSource() const
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