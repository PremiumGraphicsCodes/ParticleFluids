#include "ParticleSystemScene.h"

#include "ScreenIdShaderBuffer.h"

#include "../Graphics/DrawableId.h"
#include "ShaderScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ParticleSystemScene::ParticleSystemScene() :
	IShapeScene(-1, nullptr),
	shape(nullptr)
{}

ParticleSystemScene::ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<ParticleSystem<ParticleAttribute>> shape) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape))
{}

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