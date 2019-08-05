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

