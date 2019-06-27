#pragma once

#include "IObjectRepository.h"
#include "PolygonMeshScene.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "PolygonMeshAttribute.h"

namespace Crystal {
	namespace Model {

class SceneFactory : public IObjectRepository
{
public:
	explicit SceneFactory(ObjectIdProvider& idProvider) :
		IObjectRepository(idProvider)
	{}

	~SceneFactory();

	void clear();

	int addPolygonMeshScene(Shape::PolygonMesh* mesh, const std::string& name);

	PolygonMeshScene* findObjectById(const int id) const;

	std::list<PolygonMeshScene*> getObjects() const { return polygonMeshes; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	std::list<PolygonMeshScene*> polygonMeshes;
};

	}
}