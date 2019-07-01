#include "ParticleSystemScene.h"

#include "ObjectViewModel.h"

using namespace Crystal::Model;

void ParticleSystemScene::addViewModel(Crystal::UI::ObjectViewModel& viewModel)
{
	if (!isVisible()) {
		return;
	}
	const auto& particles = getShape()->getParticles();
	for (auto p : particles) {
		viewModel.pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
}
