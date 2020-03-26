#include "Scene.h"

#include "ScreenIdShaderBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

Scene::Scene(const int id, const std::string& name) :
	IScene(id, name)
{
}


Scene::~Scene()
{
}

Box3d Scene::getBoundingBox() const
{
	Box3d bb = Box3d::createDegeneratedBox();
	for (auto c : children) {
		if (bb.isDegenerated(1.0e-12)) {
			bb = c->getBoundingBox();
			continue;
		}
		auto b = c->getBoundingBox();
		if (b.isDegenerated(1.0e-12)) {
			continue;
		}
		bb.add(b);
	}
	if (bb.isDegenerated(1.0e-12)) {
		return Box3d();
	}

	return bb;
}

void Scene::send(ScreenIdShaderBuffer& parentIdViewModel, ScreenIdShaderBuffer& childIdViewModel) const
{
	for (auto c : children) {
		c->send(parentIdViewModel, childIdViewModel);
	}
}



