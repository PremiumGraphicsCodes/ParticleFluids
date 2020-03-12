#include "ParticleSystemScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"
#include "IRenderer.h"

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

void ParticleSystemScene::onBuild(GLObjectFactory& factory)
{
	buffer.build();
	//factory.getShaderFactory()->create()
}

void ParticleSystemScene::onSend()
{
	if (!isVisible()) {
		return;
	}
	const auto& particles = getShape()->getParticles();
	PointBuffer pointBuffer;
	pointBuffer.setMatrix(getMatrix());
	for (auto p : particles) {
		pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	buffer.send(pointBuffer);
}

void ParticleSystemScene::send(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	parentIdBuffer.setMatrix(getMatrix());
	PointBuffer childIdBuffer;
	childIdBuffer.setMatrix(getMatrix());
	for (auto p : particles) {
		Graphics::DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
		Graphics::DrawableID childDid(particleId++);
		childIdBuffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	parentIdViewModel.pointIdBuffers.push_back(parentIdBuffer);
	childIdViewModel.pointIdBuffers.push_back(childIdBuffer);
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
