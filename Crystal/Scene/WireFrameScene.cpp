#include "WireFrameScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void WireFrameScene::translate(const Vector3dd& v)
{
	for (auto& l : lines) {
		l.move(v);
	}
}

void WireFrameScene::transform(const Matrix3dd& m)
{
	for (auto& l : lines) {
		l.transform(m);
	}
}

void WireFrameScene::transform(const Matrix4dd& m)
{
	for (auto& l : lines) {
		l.transform(m);
	}
}

std::vector<Vector3dd> WireFrameScene::getAllVertices() const
{
	if (lines.empty()) {
		return std::vector<Vector3dd>();
	}

	std::vector<Vector3dd> vertices;
	for (const auto& l : lines) {
		vertices.push_back(l.getStart());
	}
	vertices.push_back(lines.back().getEnd());
	return vertices;
}

void WireFrameScene::getBoundingBox(Box3d& box) const
{
	if (lines.empty()) {
		return;
	}

	const auto& vertices = getAllVertices();
	Box3d bb(vertices.front());
	for (const auto& v : vertices) {
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
		int index = 0;
		LineBuffer buffer(getAttribute().width);
		for (const auto& l : lines) {
			buffer.addVertex(l.getStart(), color);
			buffer.addVertex(l.getEnd(), color);
			buffer.addIndex(index++);
			buffer.addIndex(index++);
		}
		viewModel.lineBuffers.push_back(buffer);
	}
	else
	{
		int index = 0;
		LineBuffer buffer(getAttribute().width * 10.0f);
		for (const auto& l : lines) {
			buffer.addVertex(l.getStart(), ColorRGBAf(1,0,0,0));
			buffer.addVertex(l.getEnd(), ColorRGBAf(1,0,0,0));
			buffer.addIndex(index++);
			buffer.addIndex(index++);
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
	for (const auto& l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		lineBuffer.addVertex(l.getStart(), did.toColor());
		lineBuffer.addIndex(index++);
	}
	viewModel.lineIdBuffers.push_back(lineBuffer);
}

Vector3dd WireFrameScene::getPosition(const int index) const
{
	return lines[index].getStart();
}

IShapeScene* WireFrameScene::clone() const
{
	return nullptr;
	//return new WireFrameScene();
}