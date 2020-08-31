#include "SceneShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShaderScene::SceneShaderScene(const std::string& name) :
	IShaderScene(name),
	screen("ScreenScene"),
	parentId("ParentIdScene"),
	childId("ChildIdScene")
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
	screen.build(glFactory);
	parentId.build(glFactory);
	childId.build(glFactory);
	return true;
}
