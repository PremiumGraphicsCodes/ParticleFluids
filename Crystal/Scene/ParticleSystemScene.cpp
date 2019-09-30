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
	if(!isSelected()) {
		PointBuffer pointBuffer;
		for (auto p : particles) {
			pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
		}
		viewModel.pointBuffers.push_back(pointBuffer);
	}
	else {
		PointBuffer pointBuffer;
		for (auto p : particles) {
			pointBuffer.add(p->getPosition(), ColorRGBAf(1, 0, 0, 0), p->getAttribute().size * 2.0f);
		}
		viewModel.pointBuffers.push_back(pointBuffer);
	}
}

void ParticleSystemScene::toIdViewModel(SceneIdViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	PointBuffer buffer;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		buffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
	viewModel.pointIdBuffers.push_back(buffer);
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
