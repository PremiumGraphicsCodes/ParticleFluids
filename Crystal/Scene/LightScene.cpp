#include "LightScene.h"

#include "SceneViewModel.h"

using namespace Crystal::Scene;

void LightScene::addViewModel(Crystal::UI::SceneViewModel& viewModel) const
{
	auto ll = getLight();
	viewModel.lightBuffer.add(*ll);
}
