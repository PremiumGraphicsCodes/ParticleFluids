#include "WireFrameScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel WireFrameScene::toViewModel() const
{
	SceneViewModel viewModel;
	if (!isVisible()) {
		return viewModel;
	}
	const auto& lines = getShape()->getLines();
	const auto& color = getAttribute().color;
	int index = 0;
	for (const auto& l : lines) {
		viewModel.lineBuffer.add(l.getStart(), color, index++);
		viewModel.lineBuffer.add(l.getEnd(), color, index++);
	}
	return viewModel;
}

SceneIdViewModel WireFrameScene::toIdViewModel() const
{
	const auto objectId = getId();
	const auto& lines = getShape()->getLines();
	int childId = 0;
	int index = 0;
	
	SceneIdViewModel viewModel;
	for (const auto& l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		viewModel.lineIdBuffer.add(l.getStart(), did.toColor(), index++);
	}
	return viewModel;
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