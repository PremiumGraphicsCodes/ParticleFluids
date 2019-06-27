#pragma once

#include "IObjectRepository.h"
#include "PolygonMeshObject.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "PolygonMeshAttribute.h"

namespace Crystal {
	namespace Model {

class PolygonMeshObjectRepository : public IObjectRepository
{
public:
	explicit PolygonMeshObjectRepository(ObjectIdProvider& idProvider) :
		IObjectRepository(idProvider)
	{}

	~PolygonMeshObjectRepository();

	void clear();

	int addObject(Shape::PolygonMesh* mesh, const std::string& name);

	PolygonMeshObject* findObjectById(const int id) const;

	std::list<PolygonMeshObject*> getObjects() const { return polygonMeshes; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	std::list<PolygonMeshObject*> polygonMeshes;
};

	}
}