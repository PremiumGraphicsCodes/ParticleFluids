#include "WireFrameScene.h"

#include "SceneIdShaderBuffer.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

WireFrameScene::WireFrameScene() :
	IShapeScene(-1, nullptr)
{}

WireFrameScene::WireFrameScene(const int id, const std::string& name, std::unique_ptr<WireFrame> shape, const WireFrameAttribute& attribute) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape)),
	attribute(attribute)
{}

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

Box3d WireFrameScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}

void WireFrameScene::send(ScreenIdShaderBuffer& parentIdViewModel, ScreenIdShaderBuffer& childIdViewModel) const
{
	if (!isVisible()) {
		return;
	}
	const auto objectId = getId();
	int childId = 0;
	int index = 0;

	const auto& positions = shape->getPositions();
	LineBuffer lineBuffer(getAttribute().width);
	lineBuffer.setMatrix(getMatrix());
	for (const auto& l : positions) {
		Graphics::DrawableID parentDid(objectId);
		Graphics::DrawableID childDid(childId++);
		lineBuffer.addVertex(l, parentDid.toColor());
		lineBuffer.addIndex(index++);
	}
	parentIdViewModel.lineIdBuffers.push_back(lineBuffer);
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
