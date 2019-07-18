#include "MaterialScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Scene;

SceneViewModel MaterialScene::toViewModel() const
{
	return SceneViewModel();
}

SceneIdViewModel MaterialScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
