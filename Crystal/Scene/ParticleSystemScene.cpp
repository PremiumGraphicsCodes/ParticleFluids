#include "ParticleSystemScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"
#include "IRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

void ParticleSystemScene::toViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto& particles = getShape()->getParticles();
	PointBuffer pointBuffer;
	pointBuffer.setMatrix(getMatrix());
	for (auto p : particles) {
		pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	viewModel.pointBuffers.push_back(pointBuffer);
}

void ParticleSystemScene::toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	parentIdBuffer.setMatrix(getMatrix());
	PointBuffer childIdBuffer;
	childIdBuffer.setMatrix(getMatrix());
	for (auto p : particles) {
		Graphics::DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
		Graphics::DrawableID childDid(particleId++);
		childIdBuffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	parentIdViewModel.pointIdBuffers.push_back(parentIdBuffer);
	childIdViewModel.pointIdBuffers.push_back(childIdBuffer);
}

Crystal::Math::Box3d ParticleSystemScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}

Vector3dd ParticleSystemScene::getPosition(const int index) const
{
	const auto& ps = getShape()->getParticles();
	return ps[index]->getPosition();
}

IShapeScene* ParticleSystemScene::clone() const
{
	return nullptr;
}

void ParticleSystemScene::setAttribute(const ParticleAttribute& attribute)
{
	auto particles = getShape()->getParticles();
	for (auto p : particles) {
		p->setAttribute(attribute);
	}
}
