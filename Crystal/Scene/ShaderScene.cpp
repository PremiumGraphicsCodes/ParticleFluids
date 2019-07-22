#include "ShaderScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneViewModel ShaderScene::toViewModel() const
{
	return SceneViewModel();
}

SceneIdViewModel ShaderScene::toIdViewModel() const
{
	return SceneIdViewModel();
}