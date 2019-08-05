#include "PointShaderScene.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

std::string PointShaderScene::getBuiltInVsSource() const
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

void PointShaderScene::render(const ICamera& camera)
{
	auto shader = getShader();

	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();

	shader->bind();

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute4df("color", colors);
	shader->sendVertexAttribute1df("pointSize", sizes);

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