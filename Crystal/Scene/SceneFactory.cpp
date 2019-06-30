#include "SceneFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

SceneFactory::SceneFactory(SceneIdProvider& idProvider):
	idProvider(idProvider)
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
	for (auto p : particleSystems) {
		delete p->getShape();
		delete p;
	}
	particleSystems.clear();

	for (auto p : polygonMeshes) {
		delete p->getShape();
		delete p;
	}
	polygonMeshes.clear();
}

int SceneFactory::addParticleSystemScene(const Vector3dd& position, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	particles->add(position, attribute);
	particleSystems.push_back(new ParticleSystemScene(getNextId(), name, particles));
	return particleSystems.back()->getId();
}

int SceneFactory::addParticleSystemScene(const std::vector<Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new ParticleSystem<ParticleAttribute>();
	for (const auto& p : positions) {
		particles->add(p, attribute);
	}
	particleSystems.push_back(new ParticleSystemScene(getNextId(), name, particles));
	return particleSystems.back()->getId();
}

int SceneFactory::addParticleSystemScene(const std::vector<Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name)
{
	assert(positions.size() == attributes.size());
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	for (int i = 0; i < positions.size(); ++i) {
		particles->add(positions[i], attributes[i]);
	}
	particleSystems.push_back(new ParticleSystemScene(getNextId(), name, particles));
	return particleSystems.back()->getId();

}

int SceneFactory::addWireFrameScene(WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name)
{
	wires.push_back(new WireFrameScene(getNextId(), name, wire, attribute));
	return wires.back()->getId();
}

int SceneFactory::addPolygonMeshScene(PolygonMesh* mesh, const std::string& name)
{
	polygonMeshes.push_back(new PolygonMeshScene(getNextId(), name, mesh));
	return polygonMeshes.back()->getId();
}

void SceneFactory::addLightScene(PointLight* l, const std::string& name)
{
	LightScene* object = new LightScene(getNextId(), name, l);
	lights.push_back(object);
}

PolygonMeshScene* SceneFactory::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(polygonMeshes), std::cend(polygonMeshes), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(polygonMeshes)) {
		return nullptr;
	}
	return *iter;
}

Box3d SceneFactory::getBoundingBox() const
{
	const auto& vertices = getAllVertices();
	if (vertices.empty()) {
		return Box3d();
	}
	Box3d bb(vertices.front());
	for (const auto& v : vertices) {
		bb.add(v);
	}
	return bb;
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
