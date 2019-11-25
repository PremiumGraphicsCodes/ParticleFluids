#include "WireFrameScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void WireFrameScene::translate(const Vector3dd& v)
{
	shape->move(v);
}

void WireFrameScene::transform(const Matrix3dd& m)
{
	shape->transform(m);
}

void WireFrameScene::transform(const Matrix4dd& m)
{
	shape->transform(m);
}

std::vector<Vector3dd> WireFrameScene::getAllVertices() const
{
	return shape->getPositions();
}

void WireFrameScene::getBoundingBox(Box3d& box) const
{
	const auto& positions = shape->getPositions();
	if (positions.empty()) {
		return;
	}
	Box3d bb(positions.front());
	for (const auto& v : positions) {
		bb.add(v);
	}
	box.add(bb);
}

void WireFrameScene::toViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	const auto& color = getAttribute().color;
	LineBuffer buffer(getAttribute().width);
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}
	for(const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	viewModel.lineBuffers.push_back(buffer);
}

void WireFrameScene::toIdViewModel(SceneIdViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	int childId = 0;
	int index = 0;

	const auto& positions = shape->getPositions();
	LineBuffer lineBuffer(getAttribute().width);
	for (const auto& l : positions) {
		Graphics::DrawableID did(objectId, childId++);
		lineBuffer.addVertex(l, did.toColor());
		lineBuffer.addIndex(index++);
	}
	viewModel.lineIdBuffers.push_back(lineBuffer);
}

Vector3dd WireFrameScene::getPosition(const int index) const
{
	const auto& positions = shape->getPositions();
	return positions[index];
}

IShapeScene* WireFrameScene::clone() const
{
	return nullptr;
	//return new WireFrameScene();
}