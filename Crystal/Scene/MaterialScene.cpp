#include "MaterialScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Scene;

void MaterialScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.materials.push_back(material);
}

void MaterialScene::toIdViewModel(SceneIdViewModel& viewModel) const
{

}
