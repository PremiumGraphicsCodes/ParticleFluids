#include "TransformScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Scene;

void TransformScene::toViewModel(SceneViewModel& viewModel) const
{
}

SceneIdViewModel TransformScene::toIdViewModel() const
{
	return SceneIdViewModel();
}
