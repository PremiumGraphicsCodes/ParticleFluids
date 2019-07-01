#include "LightScene.h"

#include "ObjectViewModel.h"

using namespace Crystal::Model;

void LightScene::addViewModel(Crystal::UI::ObjectViewModel& viewModel)
{
	auto ll = getLight();
	viewModel.lightBuffer.add(*ll);
}
