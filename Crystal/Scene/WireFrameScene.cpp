#include "WireFrameScene.h"

#include "ObjectViewModel.h"

using namespace Crystal::Model;

void WireFrameScene::addViewModel(Crystal::UI::ObjectViewModel& viewModel)
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
