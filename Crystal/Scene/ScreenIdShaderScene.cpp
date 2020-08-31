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
	const auto& children = getChildren();
	for (auto c : children) {
		c->render();
	}
}


void ScreenIdShaderScene::add(PointShaderScene* scene)
{
	scene->setCamera(camera);
	this->pointScenes.push_back(scene);
	addChild(scene);
}

void ScreenIdShaderScene::add(LineShaderScene* scene)
{
	scene->setCamera(camera);
	this->lineScenes.push_back(scene);
	addChild(scene);
}

void ScreenIdShaderScene::add(TriangleShaderScene* scene)
{
	scene->setCamera(camera);
	this->triangleIdBuffers.push_back(scene);
	addChild(scene);
}

void ScreenIdShaderScene::setCamera(CameraShaderScene* camera)
{
	this->camera = camera;
}
