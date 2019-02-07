#include "ObjectIdViewModel.h"
#include "Repository.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void ObjectIdViewModel::add(ObjectRepository& objects)
{
	const auto& particleSystems = objects.getParticleSystems()->getObjects();
	for (const auto& ps : particleSystems) {
		add(ps);
	}
}

void ObjectIdViewModel::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointIdBuffer.add(pos, c, size);
}

void ObjectIdViewModel::add(const ParticleSystemObject& object)
{
	const auto particleSystemId = object.getId();
	const auto& particles = object.getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(particleId++, particleSystemId);
		pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
}

void ObjectIdViewModel::add(const PolygonMeshObject& object)
{

}
