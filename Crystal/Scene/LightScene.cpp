#include "LightScene.h"

#include "SceneViewModel.h"

using namespace Crystal::Scene;

void LightScene::addViewModel(Crystal::Scene::SceneViewModel& viewModel) const
{
	auto ll = getLight();
	viewModel.lightBuffer.add(*ll);
}
