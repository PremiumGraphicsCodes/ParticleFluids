#include "SceneShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

void SceneShaderScene::setCamera(CameraShaderScene* camera)
{
	screen.setCamera(camera);
	parentId.setCamera(camera);
	childId.setCamera(camera);
	//addChild(camera);
}