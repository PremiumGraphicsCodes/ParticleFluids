#include "IdViewModel.h"
#include "Repository.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void IdViewModel::add(ObjectRepository& objects)
{
	const auto& particleSystems = objects.getParticleSystems()->getObjects();
	for (const auto& ps : particleSystems) {
		add(ps);
	}
}

void IdViewModel::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointIdBuffer.add(pos, c, size);
}

void IdViewModel::add(const ParticleSystemObject& object)
{
	const auto particleSystemId = object.getId();
	const auto& particles = object.getShape()->getParticles();
	int particleId = 1;
	for (auto p : particles) {
		particleId++;
		Graphics::DrawableID did(particleSystemId, particleId++);
		//		pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size());
	}
}
