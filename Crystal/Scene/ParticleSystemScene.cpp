#include "ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ParticleSystemScene::ParticleSystemScene() :
	IShapeScene(-1, nullptr),
	shape(nullptr),
	controller(this)
{}

ParticleSystemScene::ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<ParticleSystem<ParticleAttribute>> shape) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape)),
	controller(this)
{}

ParticleSystemScene::ParticleSystemScene(const int id, const Vector3dd& position, const ParticleAttribute& attribute, const std::string& name) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape)),
	controller(this)
{
	shape->add(position, attribute);
}

ParticleSystemScene::ParticleSystemScene(const int id, const std::vector<Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape)),
	controller(this)
{
	for (const auto& p : positions) {
		shape->add(p, attribute);
	}
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