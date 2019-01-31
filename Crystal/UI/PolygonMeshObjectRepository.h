#pragma once

#include "PolygonMeshObject.h"

namespace Crystal {
	namespace UI {

class PolygonMeshObjectRepository
{
public:
	PolygonMeshObjectRepository() :
		nextId(1)
	{}

	~PolygonMeshObjectRepository();

	void clear();

	int addObject(Shape::PolygonMesh* mesh, const Graphics::Material& material, const std::string& name);

	std::list<PolygonMeshObject> getPolygonMeshes() const { return polygonMeshes; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

private:
	int nextId;
	std::list<PolygonMeshObject> polygonMeshes;
};

	}
}