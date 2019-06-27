#include "Scene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

Scene::Scene() :
	particleSystems(idProvider),
	wireFrames(idProvider),
	polygonMeshes(idProvider)
{
}

Scene::~Scene()
{
	clear();
}

void Scene::clear()
{
	particleSystems.clear();
	wireFrames.clear();
	polygonMeshes.clear();
}

Box3d Scene::getBoundingBox() const
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

std::list<Vector3dd> Scene::getAllVertices() const
{
	std::list<Vector3dd> positions;
	const auto& particles = particleSystems.getAllVertices();
	positions.insert(positions.end(), particles.begin(), particles.end());
	const auto& wires = wireFrames.getAllVertices();
	positions.insert(positions.end(), wires.begin(), wires.end());
	const auto& meshes = polygonMeshes.getAllVertices();
	positions.insert(positions.end(), meshes.begin(), meshes.end());
	return positions;
}

std::list<IScene*> Scene::getAllObjects() const
{
	std::list<IScene*> objects;
	const auto& ps = particleSystems.getObjects();
	for (auto p : ps) {
		objects.push_back(p);
	}
	auto& ws = wireFrames.getObjects();
	for (auto w : ws) {
		objects.push_back(w);
	}
	auto& polygons = polygonMeshes.getObjects();
	for (auto& p : polygons) {
		objects.push_back(p);
	}
	return objects;
}

IScene* Scene::findObjectById(const int id)
{
	const auto& objects = getAllObjects();
	auto iter = std::find_if(std::cbegin(objects), std::cend(objects), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(objects)) {
		return nullptr;
	}
	return *iter;
}
