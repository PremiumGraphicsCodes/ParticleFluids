#include "ParticleSystemScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Model;

void ParticleSystemScene::addViewModel(Crystal::UI::SceneViewModel& viewModel)
{
	if (!isVisible()) {
		return;
	}
	const auto& particles = getShape()->getParticles();
	for (auto p : particles) {
		viewModel.pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
}

void ParticleSystemScene::addViewModel(Crystal::UI::SceneIdViewModel& viewModel)
{
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		viewModel.pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
}
