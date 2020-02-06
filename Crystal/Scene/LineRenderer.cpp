#include "LineRenderer.h"
#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

LineRenderer::LineRenderer()
{
}

bool LineRenderer::build(GLObjectFactory& factory)
{
	setVertexShaderSource(getBuiltInVsSource());
	setFragmentShaderSource(getBuiltInFsSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");

	addAttribute("position");
	addAttribute("color");

	glBuffer.vbo.vertex.build();
	glBuffer.vbo.color.build();

	glBuffer.vao.build();

	return build_(factory);
}

void LineRenderer::send(const LineBuffer& buffer)
{
	const auto positions = buffer.getPositions().get();
	const auto colors = buffer.getColors().get();
	if (positions.empty()) {
		return;
	}

	glBuffer.vbo.vertex.send(positions);
	glBuffer.vbo.color.send(colors);

	auto shader = getShader();

	glBuffer.vao.bind();
	shader->sendVertexAttribute3df("position", glBuffer.vbo.vertex);
	shader->sendVertexAttribute4df("color", glBuffer.vbo.color);
	glBuffer.vao.unbind();

	this->indices = buffer.getIndices().get();
	this->matrix = buffer.getMatrix();
	this->lineWidth = buffer.getWidth();
}

void LineRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix() * matrix;

	shader->bind();

	shader->setLineWidth(lineWidth);
	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	glBuffer.vao.bind();
	shader->drawLines(indices);
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