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
	int index = 0;
	LineBuffer lineBuffer(1.0f);
	for (const auto& l : lines) {
		lineBuffer.add(l.getStart(), color, index++);
		lineBuffer.add(l.getEnd(), color, index++);
	}
	viewModel.lineBuffers.push_back(lineBuffer);
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
	
	for (const auto& l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		viewModel.lineIdBuffer.add(l.getStart(), did.toColor(), index++);
	}
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