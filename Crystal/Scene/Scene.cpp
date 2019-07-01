#include "Scene.h"

#include "SceneViewModel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

Scene::Scene()
{
}

Scene::~Scene()
{
	clear();
}

void Scene::onClear()
{
	factory.clear();
}

Box3d Scene::getBoundingBox() const
{
	Box3d bb;
	for (auto c : children) {
		c->getBoundingBox(bb);
	}

	return bb;
}

std::list<Vector3dd> Scene::getAllVertices() const
{
	std::list<Vector3dd> positions;
	/*

	const auto& particles = particleSystems.getAllVertices();
	positions.insert(positions.end(), particles.begin(), particles.end());
	const auto& wires = polygonMeshes.getWires().getAllVertices();
	positions.insert(positions.end(), wires.begin(), wires.end());
	*/
	const auto& meshes = factory.getAllVertices();
	positions.insert(positions.end(), meshes.begin(), meshes.end());
	return positions;
}

std::list<IScene*> Scene::getAllObjects() const
{
	std::list<IScene*> objects;
	/*
	const auto& ps = particleSystems.getObjects();
	for (auto p : ps) {
		objects.push_back(p);
	}
	auto& ws = wireFrames.getObjects();
	for (auto w : ws) {
		objects.push_back(w);
	}
	*/
	auto& polygons = factory.getPolygonMeshes();
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

void Scene::addViewModel(Crystal::UI::SceneViewModel& viewModel)
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}

void Scene::addViewModel(Crystal::UI::SceneIdViewModel& viewModel)
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}



