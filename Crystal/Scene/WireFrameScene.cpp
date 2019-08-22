#include "WireFrameScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void WireFrameScene::toViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto& lines = getShape()->getLines();
	const auto& color = getAttribute().color;
	{
		int index = 0;
		LineBuffer lineBuffer(getAttribute().width);
		for (const auto& l : lines) {
			lineBuffer.add(l.getStart(), color, index++);
			lineBuffer.add(l.getEnd(), color, index++);
		}
		viewModel.lineBuffers.push_back(lineBuffer);
	}
	if (isSelected())
	{
		int index = 0;
		LineBuffer lb(getAttribute().width * 10.0f);
		for (const auto& l : lines) {
			lb.add(l.getStart(), ColorRGBAf(1,0,0,0), index++);
			lb.add(l.getEnd(), ColorRGBAf(1,0,0,0), index++);
		}
		viewModel.lineBuffers.push_back(lb);
	}
}

void WireFrameScene::toIdViewModel(SceneIdViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	const auto& lines = getShape()->getLines();
	int childId = 0;
	int index = 0;

	LineBuffer lineBuffer(getAttribute().width);
	for (const auto& l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		lineBuffer.add(l.getStart(), did.toColor(), index++);
	}
	viewModel.lineIdBuffers.push_back(lineBuffer);
}

void WireFrameScene::getBoundingBox(Crystal::Math::Box3d& box) const
{
	box.add( getShape()->getBoundingBox() );
}

Vector3dd WireFrameScene::getPosition(const int index) const
{
	const auto& vertices = getShape()->getVertices();
	return vertices[index];
}