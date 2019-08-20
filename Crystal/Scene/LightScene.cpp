#include "LightScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel LightScene::toViewModel() const
{
	SceneViewModel viewModel;
	viewModel.lights.push_back(light);
	return viewModel;
}

SceneIdViewModel LightScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
