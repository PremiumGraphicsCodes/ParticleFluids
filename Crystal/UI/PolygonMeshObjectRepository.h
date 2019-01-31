#pragma once

#include "IObjectRepository.h"
#include "PolygonMeshObject.h"

namespace Crystal {
	namespace UI {

class PolygonMeshObjectRepository : public IObjectRepository
{
public:
	PolygonMeshObjectRepository() :
		nextId(1)
	{}

	~PolygonMeshObjectRepository();

	void clear();

	int addObject(Shape::PolygonMesh* mesh, const Graphics::Material& material, const std::string& name);

	std::list<PolygonMeshObject> getObjects() const { return polygonMeshes; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	int nextId;
	std::list<PolygonMeshObject> polygonMeshes;
};

	}
}