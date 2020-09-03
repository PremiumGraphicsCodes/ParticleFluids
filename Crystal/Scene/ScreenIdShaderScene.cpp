#include "ScreenIdShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

#include "PointShaderScene.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Scene;

ScreenIdShaderScene::ScreenIdShaderScene()
{
}

void ScreenIdShaderScene::add(PointShaderScene* scene)
{
	scene->setCamera(camera);
	this->scenes.push_back(scene);
}

void ScreenIdShaderScene::add(LineShaderScene* scene)
{
	scene->setCamera(camera);
	this->scenes.push_back(scene);
}

void ScreenIdShaderScene::add(TriangleShaderScene* scene)
{
	scene->setCamera(camera);
	this->scenes.push_back(scene);
}

void ScreenIdShaderScene::setCamera(CameraShaderScene* camera)
{
	this->camera = camera;
}
