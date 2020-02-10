#include "TriangleRenderer.h"

#include <sstream>

#include "../Shader/VertexBufferObject.h"


using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

namespace {
}

void TriangleRenderer::GLBuffer::build()
{
	vbo.position.build();
	vbo.color.build();
}

void TriangleRenderer::GLBuffer::send(const LineBuffer& buffer)
{
	vbo.position.send(buffer.getPositions().get());
	vbo.color.send(buffer.getColors().get());

	indices = buffer.getIndices().get();
}

TriangleRenderer::TriangleRenderer()
{
}

bool TriangleRenderer::build(GLObjectFactory& factory)
{
	setVertexShaderSource(getBuildInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");

	addAttribute("position");
	addAttribute("color");

	return build_(factory);
}

void TriangleRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix();

	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	shader->sendVertexAttribute3df("position", glBuffer.vbo.position);
	shader->sendVertexAttribute4df("color", glBuffer.vbo.color);

	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("color");

	shader->drawTriangles(glBuffer.indices);

	shader->disableVertexAttribute("color");
	shader->disableVertexAttribute("position");

	shader->disableDepthTest();

	shader->unbind();
}

std::string TriangleRenderer::getBuildInVertexShaderSource() const
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

std::string TriangleRenderer::getBuiltInFragmentShaderSource() const
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
