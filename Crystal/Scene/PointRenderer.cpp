#include "PointRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

PointRenderer::PointRenderer()
{
}

bool PointRenderer::build(GLObjectFactory& factory)
{
	setVertexShaderSource(getBuiltInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");

	addAttribute("position");
	addAttribute("color");
	addAttribute("pointSize");

	return build_(factory);
}

void PointRenderer::send(const PointBuffer& buffer)
{
	auto shader = getShader();

	this->buffer = buffer;

	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute4df("color", colors);
	shader->sendVertexAttribute1df("pointSize", sizes);

	/*
	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("color");
	shader->enableVertexAttribute("pointSize");
	*/
}

void PointRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto modelviewMatrix = camera.getModelViewMatrix() * Matrix4df(buffer.getMatrix());

	shader->bind();

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	/*
	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute4df("color", colors);
	shader->sendVertexAttribute1df("pointSize", sizes);
	*/

	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("color");
	shader->enableVertexAttribute("pointSize");

	shader->drawPoints(positions.size() / 3);

	shader->disableVertexAttribute("pointSize");
	shader->disableVertexAttribute("color");
	shader->disableVertexAttribute("position");

	shader->bindOutput("fragColor");

	shader->disablePointSprite();
	shader->disableDepthTest();

	shader->unbind();
}

std::string PointRenderer::getBuiltInVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vColor = color;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string PointRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec2 coord = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = 1.0 - dot(coord, coord);" << std::endl
		<< "	if (distSquared < 0.0) {" << std::endl
		<< "		discard;" << std::endl
		<< "	}" << std::endl
		<< "	fragColor.rgba = vColor;" << std::endl
		//		<< "	fragColor.a = sqrt(distSquared) * vColor.a;" << std::endl
		//		<< "	fragColor.a = 0.1;//sqrt(distSquared);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}