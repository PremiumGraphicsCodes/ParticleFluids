#include "LightScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel LightScene::toViewModel() const
{
	SceneViewModel viewModel;
	viewModel.lightBuffer.add(light);
	return viewModel;
}

SceneIdViewModel LightScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
