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
	const auto objectId = object.getId();
	const auto& particles = object.getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
}

void ObjectIdViewModel::add(const WireFrameObject& object)
{
	const auto objectId = object.getId();
	const auto& lines = object.getShape()->getLines();
	int childId = 0;
	int index = 0;
	for (auto l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		lineIdBuffer.add(l.getStart(), did.toColor(), index++);
	}
}

void ObjectIdViewModel::add(const PolygonMeshObject& object)
{
	const auto objectId = object.getId();
	const auto& faces = object.getShape()->getFaces();
	int faceId = 0;
	for (auto f : faces) {
		Graphics::DrawableID did(objectId, faceId++);
		//triangleIdBuffer.add()
	}
}
