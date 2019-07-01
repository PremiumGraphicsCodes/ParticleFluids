#include "SceneFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

SceneFactory::SceneFactory()
{
	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPosition(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	addLightScene(light, "Light");
}

SceneFactory::~SceneFactory()
{
	clear();
}

void SceneFactory::clear()
{
	for (auto p : polygonMeshes) {
		delete p->getShape();
		delete p;
	}
	polygonMeshes.clear();
}

ParticleSystemScene* SceneFactory::addParticleSystemScene(const Vector3dd& position, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	particles->add(position, attribute);
	return new ParticleSystemScene(getNextId(), name, particles);
}

ParticleSystemScene* SceneFactory::addParticleSystemScene(const std::vector<Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	for (const auto& p : positions) {
		particles->add(p, attribute);
	}
	return new ParticleSystemScene(getNextId(), name, particles);
}

ParticleSystemScene* SceneFactory::addParticleSystemScene(const std::vector<Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name)
{
	assert(positions.size() == attributes.size());
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	for (int i = 0; i < positions.size(); ++i) {
		particles->add(positions[i], attributes[i]);
	}
	return new ParticleSystemScene(getNextId(), name, particles);
}

WireFrameScene* SceneFactory::addWireFrameScene(WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name)
{
	return new WireFrameScene(getNextId(), name, wire, attribute);
}

int SceneFactory::addPolygonMeshScene(PolygonMesh* mesh, Material* m, const std::string& name)
{
	MaterialScene* material = new MaterialScene(getNextId(), name, m);
	polygonMeshes.push_back(new PolygonMeshScene(getNextId(), name, mesh, material));
	return polygonMeshes.back()->getId();
}

void SceneFactory::addLightScene(PointLight* l, const std::string& name)
{
	LightScene* object = new LightScene(getNextId(), name, l);
	lights.push_back(object);
}

MaterialScene* SceneFactory::addMaterialScene(Material* m, const std::string& name)
{
	return new MaterialScene(getNextId(), name, m);
}

std::list<Vector3dd> SceneFactory::getAllVertices() const
{
	std::list<Vector3dd> positions;
	for (const auto& ps : polygonMeshes) {
		const auto& vs = ps->getShape()->getVertices();
		for (const auto& p : vs) {
			positions.push_back(p->getPosition());
		}
	}
	return positions;
}
