#include "ParticleSystemScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"
#include "ShaderScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneViewModel ParticleSystemScene::toViewModel() const
{
	SceneViewModel viewModel;
	if (!isVisible()) {
		return viewModel;
	}
	const auto& particles = getShape()->getParticles();
	for (auto p : particles) {
		viewModel.pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	return viewModel;
}

SceneIdViewModel ParticleSystemScene::toIdViewModel() const
{
	SceneIdViewModel viewModel;
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		viewModel.pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
	return viewModel;
}

void ParticleSystemScene::getBoundingBox(Crystal::Math::Box3d& box) const
{
	box.add(getShape()->getBoundingBox());
}

Vector3dd ParticleSystemScene::getPosition(const int index) const
{
	const auto& ps = getShape()->getParticles();
	return ps[index]->getPosition();
}

bool ParticleSystemScene::onBuild()
{
	if (!isVisible()) {
		return true;
	}
	const auto& particles = getShape()->getParticles();
	for (auto p : particles) {
		shaderCommand.buffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	return true;
}

IShaderCommand* ParticleSystemScene::toShaderCommand()
{
	return &shaderCommand;
}

void PointShaderCommand::execute(ShaderObject* shader)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera->getProjectionMatrix();
	const auto& modelviewMatrix = camera->getModelviewMatrix();

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