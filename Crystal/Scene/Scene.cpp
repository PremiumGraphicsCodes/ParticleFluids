#include "Scene.h"

#include "ScreenIdShaderScene.h"

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
		if (bb.isDegenerated()) {
			bb = c->getBoundingBox();
			continue;
		}
		auto b = c->getBoundingBox();
		if (b.isDegenerated()) {
			continue;
		}
		bb.add(b);
	}
	if (bb.isDegenerated()) {
		return Box3d();
	}

	return bb;
}



