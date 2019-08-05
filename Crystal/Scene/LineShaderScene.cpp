#include "LineShaderScene.h"
#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

LineShaderScene::LineShaderScene(const int id, const std::string& name) :
	ShaderScene(id, name)
{
	setVertexShaderSource(getBuiltInVsSource());
	setFragmentShaderSource(getBuiltInFsSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");

	addAttribute("position");
	addAttribute("color");
}

void LineShaderScene::render(const ICamera& camera)
{
	auto shader = getShader();

	const auto& indices = buffer.getIndices().get();
	const auto& positions = buffer.getPositions().get();
	const auto& colors = buffer.getColors().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();

	//assert(GL_NO_ERROR == glGetError());

	shader->bind();

	shader->setLineWidth(width);
	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute4df("color", colors);

	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("color");

	shader->drawLines(indices);

	shader->disableVertexAttribute("color");
	shader->disableVertexAttribute("position");

	shader->bindOutput("fragColor");

	shader->setLineWidth(1);
	shader->disableDepthTest();

	shader->unbind();
}

std::string LineShaderScene::getBuiltInVsSource() const
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

std::string LineShaderScene::getBuiltInFsSource() const
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