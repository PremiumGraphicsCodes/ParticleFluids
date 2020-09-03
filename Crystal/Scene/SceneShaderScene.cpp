#include "SceneShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

void SceneShaderScene::addScene(IShaderScene* scene)
{
	this->screenScenes.push_back(scene);
}

void SceneShaderScene::addParentIdScene(IShaderScene* scene)
{
	this->parentIdScenes.push_back(scene);
}

void SceneShaderScene::addChildIdScene(IShaderScene* scene)
{
	this->childIdScenes.push_back(scene);
}
