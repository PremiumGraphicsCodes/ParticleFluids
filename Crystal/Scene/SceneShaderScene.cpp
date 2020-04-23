#include "SceneShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShaderScene::SceneShaderScene(const std::string& name) :
	IShaderScene(name),
	screen("ScreenScene"),
	parentId("ParentIdScene"),
	childId("ChildIdScene")
{
	addChild(&screen);
}
