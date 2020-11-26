#include "ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ParticleSystemScene::ParticleSystemScene() :
	IShapeScene(-1, nullptr),
	shape(nullptr)
{
	controller = std::make_unique<ParticleSystemPresenter>(this);
}

ParticleSystemScene::ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<ParticleSystem<ParticleAttribute>> shape) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape))
{
	controller = std::make_unique<ParticleSystemPresenter>(this);
}

Crystal::Math::Box3d ParticleSystemScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}

void ParticleSystemScene::setAttribute(const ParticleAttribute& attribute)
{
	auto particles = getShape()->getParticles();
	for (auto p : particles) {
		p->setAttribute(attribute);
	}
}