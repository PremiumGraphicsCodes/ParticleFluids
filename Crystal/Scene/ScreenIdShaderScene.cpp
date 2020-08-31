#include "ScreenIdShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

#include "PointShaderScene.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Scene;

ScreenIdShaderScene::ScreenIdShaderScene(const std::string& name) :
	IShaderScene(name)
{
}

void ScreenIdShaderScene::render()
{
	for (auto c : pointScenes) {
		c->render();
	}
	for (auto c : lineScenes) {
		c->render();
	}
	for (auto t : triangleIdBuffers) {
		t->render();
	}
}

void ScreenIdShaderScene::add(PointShaderScene* scene)
{
	scene->setCamera(camera);
	this->pointScenes.push_back(scene);
}

void ScreenIdShaderScene::add(LineShaderScene* scene)
{
	scene->setCamera(camera);
	this->lineScenes.push_back(scene);
}

void ScreenIdShaderScene::add(TriangleShaderScene* scene)
{
	scene->setCamera(camera);
	this->triangleIdBuffers.push_back(scene);
}

void ScreenIdShaderScene::setCamera(CameraShaderScene* camera)
{
	this->camera = camera;
}
