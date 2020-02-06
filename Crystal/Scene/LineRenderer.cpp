#include "LineRenderer.h"
#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr const char* positionLabel = "position";
	constexpr const char* colorLabel = "color";
}

void LineRenderer::GLBuffer::build()
{
	vbo.position.build();
	vbo.color.build();

	vao.build();
}

void LineRenderer::GLBuffer::send(const LineBuffer& buffer)
{
	const auto positions = buffer.getPositions().get();
	const auto colors = buffer.getColors().get();
	if (positions.empty()) {
		return;
	}

	vbo.position.send(positions);
	vbo.color.send(colors);

	indices = buffer.getIndices().get();
	matrix = buffer.getMatrix();
	lineWidth = buffer.getWidth();
}

LineRenderer::LineRenderer()
{
}

bool LineRenderer::build(GLObjectFactory& factory)
{
	setVertexShaderSource(getBuiltInVsSource());
	setFragmentShaderSource(getBuiltInFsSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");

	addAttribute(positionLabel);
	addAttribute(colorLabel);

	return build_(factory);
}

void LineRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix() * glBuffer.matrix;

	shader->bind();

	shader->setLineWidth(glBuffer.lineWidth);
	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	glBuffer.vao.bind();
	shader->sendVertexAttribute3df(positionLabel, glBuffer.vbo.position);
	shader->sendVertexAttribute4df(colorLabel, glBuffer.vbo.color);

	shader->drawLines(glBuffer.indices);
	glBuffer.vao.unbind();

	//shader->disableVertexAttribute("color");
	//shader->disableVertexAttribute("position");

	shader->bindOutput("fragColor");

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