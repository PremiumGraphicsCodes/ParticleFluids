#include "PolygonMeshScene.h"

#include "../Graphics/DrawableId.h"
#include "../Math/Line3d.h"

#include "LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

PolygonMeshScene::PolygonMeshScene() :
	IShapeScene(-1),
	shape(nullptr)
{
	presenter = std::make_unique<PolygonMeshPresenter>(this);
}

PolygonMeshScene::PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<PolygonMesh> shape) :
	IShapeScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<PolygonMeshPresenter>(this);
}

PolygonMeshScene::~PolygonMeshScene()
{

}

Box3d PolygonMeshScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}