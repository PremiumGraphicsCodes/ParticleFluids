#include "LightScene.h"

#include "SceneViewModel.h"

using namespace Crystal::Model;

void LightScene::addViewModel(Crystal::UI::SceneViewModel& viewModel)
{
	auto ll = getLight();
	viewModel.lightBuffer.add(*ll);
}
