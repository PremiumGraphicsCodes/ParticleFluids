#include "WireFrameScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void WireFrameScene::translate(const Vector3dd& v)
{
	for (auto& l : positions) {
		l += v;
	}
}

void WireFrameScene::transform(const Matrix3dd& m)
{
	for (auto& l : positions) {
		l = m * l;
	}
}

void WireFrameScene::transform(const Matrix4dd& m)
{
	for (auto& l : positions) {
		l = m * glm::vec4(l, 1.0);
	}
}

std::vector<Vector3dd> WireFrameScene::getAllVertices() const
{
	return positions;
}

void WireFrameScene::getBoundingBox(Box3d& box) const
{
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
	const auto& color = getAttribute().color;
	if(!isSelected())
	{
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
	else
	{
		LineBuffer buffer(getAttribute().width * 10.0f);
		for (const auto& l : positions) {
			buffer.addVertex(l, ColorRGBAf(1, 0, 0, 0));
		}
		for (const auto& e : edges) {
			buffer.addIndex(e.originId);
			buffer.addIndex(e.destId);
		}
		viewModel.lineBuffers.push_back(buffer);
	}
}

void WireFrameScene::toIdViewModel(SceneIdViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	int childId = 0;
	int index = 0;

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
	return positions[index];
}

IShapeScene* WireFrameScene::clone() const
{
	return nullptr;
	//return new WireFrameScene();
}