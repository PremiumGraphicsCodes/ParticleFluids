#include "PolygonMeshScene.h"

#include "../Graphics/DrawableId.h"
#include "../Math/Line3d.h"

#include "LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

PolygonMeshScene::PolygonMeshScene() :
	IShapeScene(-1, nullptr),
	shape(nullptr),
	controller(this)
{}

PolygonMeshScene::PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<PolygonMesh> shape) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape)),
	controller(this)
{}

PolygonMeshScene::~PolygonMeshScene()
{
	for (auto g : groups) {
		delete g;
	}
}

Box3d PolygonMeshScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}