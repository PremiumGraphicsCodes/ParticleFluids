#include "LightScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel LightScene::toViewModel() const
{
	LightBuffer lb;
	lb.add(getLight());
	SceneViewModel viewModel;
	viewModel.lightBuffers.push_back(lb);
	return viewModel;
}

SceneIdViewModel LightScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
