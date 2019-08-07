#include "LightScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel LightScene::toViewModel() const
{
	SceneViewModel viewModel;
	LightBuffer lb;
	lb.add(light);
	viewModel.lightBuffers.push_back(lb);
	return viewModel;
}

SceneIdViewModel LightScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
