#include "ParticleSystemScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel ParticleSystemScene::toViewModel() const
{
	SceneViewModel viewModel;
	if (!isVisible()) {
		return viewModel;
	}
	const auto& particles = getShape()->getParticles();
	PointBuffer pointBuffer;
	for (auto p : particles) {
		pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	viewModel.pointBuffers.push_back(pointBuffer);
	return viewModel;
}

void ParticleSystemScene::addViewModel(SceneIdViewModel& viewModel) const
{
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		viewModel.pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
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