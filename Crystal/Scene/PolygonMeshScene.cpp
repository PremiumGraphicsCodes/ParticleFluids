#include "PolygonMeshScene.h"
#include "ScreenIdShaderBuffer.h"

#include "../Graphics/DrawableId.h"
#include "../Math/Line3d.h"

#include "LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

PolygonMeshScene::PolygonMeshScene() :
	IShapeScene(-1, nullptr),
	shape(nullptr)
{}

PolygonMeshScene::PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<PolygonMesh> shape) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape))
{}

Box3d PolygonMeshScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}

Vector3dd PolygonMeshScene::getPosition(const int index) const
{
	const auto& positions = getShape()->getPositions();
	return positions[index];
}

IShapeScene* PolygonMeshScene::clone() const
{
	return nullptr;
}