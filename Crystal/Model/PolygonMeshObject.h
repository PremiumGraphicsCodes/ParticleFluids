#pragma once

#include "IObject.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Model {

class PolygonMeshObject : public IObject
{
public:
	PolygonMeshObject() :
		IObject(),
		shape(nullptr)
	{}

	PolygonMeshObject(const int id, const std::string& name, Shape::PolygonMesh* shape, const int materialId) :
		IObject(id, name),
		shape(shape),
		materialId(materialId)
	{}

	~PolygonMeshObject() {};

	Shape::PolygonMesh* getShape() const { return shape; }

	int getMaterialId() const { return materialId; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const override { return shape == nullptr; }

	ObjectType getType() const override { return ObjectType::PolygonMeshObject; }

private:
	Shape::PolygonMesh* shape;
	int materialId;
};

	}
}