#include "LineShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

void LineShaderScene::render(const ICamera& camera)
{
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