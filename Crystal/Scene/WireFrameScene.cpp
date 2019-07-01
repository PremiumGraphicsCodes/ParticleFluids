#include "WireFrameScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Model;

void WireFrameScene::addViewModel(Crystal::UI::SceneViewModel& viewModel)
{
	if (!isVisible()) {
		return;
	}
	const auto& lines = getShape()->getLines();
	const auto& color = getAttribute().color;
	int index = 0;
	for (const auto& l : lines) {
		viewModel.lineBuffer.add(l.getStart(), color, index++);
		viewModel.lineBuffer.add(l.getEnd(), color, index++);
	}
}

void WireFrameScene::addViewModel(Crystal::UI::SceneIdViewModel& viewModel)
{
	const auto objectId = getId();
	const auto& lines = getShape()->getLines();
	int childId = 0;
	int index = 0;
	for (auto l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		viewModel.lineIdBuffer.add(l.getStart(), did.toColor(), index++);
	}
}