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
	LineBuffer lineBuffer;
	for (const auto& l : lines) {
		lineBuffer.add(l.getStart(), color, index++);
		lineBuffer.add(l.getEnd(), color, index++);
	}
	viewModel.lineBuffers.push_back(lineBuffer);
	return viewModel;
}

void WireFrameScene::addViewModel(SceneIdViewModel& viewModel) const
{
	const auto objectId = getId();
	const auto& lines = getShape()->getLines();
	int childId = 0;
	int index = 0;
	
	LineBuffer lineIdBuffer;
	for (auto l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		lineIdBuffer.add(l.getStart(), did.toColor(), index++);
	}
	viewModel.lineIdBuffers.push_back(lineIdBuffer);
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
