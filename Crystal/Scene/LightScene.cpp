#include "LightScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void LightScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.lights.push_back(light);
}

SceneIdViewModel LightScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
