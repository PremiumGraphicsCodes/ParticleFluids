#include "SceneShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShaderScene::SceneShaderScene(const std::string& name) :
	IShaderScene(name)
{
}

void SceneShaderScene::setCamera(CameraShaderScene* camera)
{
	screen.setCamera(camera);
	parentId.setCamera(camera);
	childId.setCamera(camera);
	//addChild(camera);
}

bool SceneShaderScene::build(GLObjectFactory& glFactory)
{
	return true;
}
