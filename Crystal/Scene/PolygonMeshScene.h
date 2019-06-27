#pragma once

#include "IScene.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Model {

class PolygonMeshScene : public IScene
{
public:
	PolygonMeshScene() :
		IScene(),
		shape(nullptr)
	{}

	PolygonMeshScene(const int id, const std::string& name, Shape::PolygonMesh* shape) :
		IScene(id, name),
		shape(shape)
	{}

	~PolygonMeshScene() {};

	Shape::PolygonMesh* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const override { return shape == nullptr; }

	ObjectType getType() const override { return ObjectType::PolygonMeshObject; }

private:
	Shape::PolygonMesh* shape;
};

	}
}