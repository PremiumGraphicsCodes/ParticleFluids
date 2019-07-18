#pragma once

#include "IShapeScene.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "MaterialScene.h"

namespace Crystal {
	namespace Scene {

class PolygonMeshScene : public IShapeScene
{
public:
	PolygonMeshScene() :
		IShapeScene(-1),
		shape(nullptr)
	{}

	PolygonMeshScene(const int id, const std::string& name, Shape::PolygonMesh* shape) :
		IShapeScene(id, name),
		shape(shape)
	{}

	~PolygonMeshScene() {};

	Shape::PolygonMesh* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::PolygonMeshScene; }

	void onClear() override
	{
		delete shape;
	}

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

	void getBoundingBox(Math::Box3d& boundingBox) const override;

	Math::Vector3dd getPosition(const int index) const override;

private:
	Shape::PolygonMesh* shape;
};

	}
}