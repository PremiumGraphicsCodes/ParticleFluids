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
	this->scenes.push_back(scene);
}

void ScreenIdShaderScene::add(LineShaderScene* scene)
{
	this->scenes.push_back(scene);
}

void ScreenIdShaderScene::add(TriangleShaderScene* scene)
{
	this->scenes.push_back(scene);
}
