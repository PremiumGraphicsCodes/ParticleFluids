#include "SceneFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

SceneFactory::SceneFactory()
{
}

SceneFactory::~SceneFactory()
{
	clear();
}

void SceneFactory::clear()
{
	idProvider.reset();
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const Vector3dd& position, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	particles->add(position, attribute);
	return new ParticleSystemScene(getNextId(), name, particles);
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	for (const auto& p : positions) {
		particles->add(p, attribute);
	}
	return new ParticleSystemScene(getNextId(), name, particles);
}

ParticleSystemScene* SceneFactory::createParticleSystemScene(const std::vector<Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name)
{
	assert(positions.size() == attributes.size());
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	for (int i = 0; i < positions.size(); ++i) {
		particles->add(positions[i], attributes[i]);
	}
	return new ParticleSystemScene(getNextId(), name, particles);
}

WireFrameScene* SceneFactory::createWireFrameScene(WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name)
{
	return new WireFrameScene(getNextId(), name, wire, attribute);
}

PolygonMeshScene* SceneFactory::createPolygonMeshScene(PolygonMesh* mesh,  const std::string& name)
{
	return new PolygonMeshScene(getNextId(), name, mesh);
}

LightScene* SceneFactory::createLightScene(PointLight* l, const std::string& name)
{
	return new LightScene(getNextId(), name, l);
}

MaterialScene* SceneFactory::createMaterialScene(Material* m, const std::string& name)
{
	return new MaterialScene(getNextId(), name, m);
}
