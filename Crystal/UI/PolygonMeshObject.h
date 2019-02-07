#pragma once

#include "IObject.h"
#include "../Shape/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace UI {

class PolygonMeshObject : public IObject
{
public:
	PolygonMeshObject(const int id, const std::string& name, Shape::PolygonMesh* shape, const Graphics::Material& material) :
		IObject(id, name),
		shape(shape),
		material(material)
	{}

	~PolygonMeshObject() {};

	Shape::PolygonMesh* getShape() const { return shape; }

	Graphics::Material getMaterial() const { return material; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

private:
	Shape::PolygonMesh* shape;
	Graphics::Material material;
};

	}
}