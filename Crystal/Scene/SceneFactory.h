#pragma once

#include "IObjectRepository.h"
#include "PolygonMeshScene.h"
#include "WireFrameScene.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "PolygonMeshAttribute.h"

namespace Crystal {
	namespace Model {

class SceneFactory : public IObjectRepository
{
public:
	explicit SceneFactory(SceneIdProvider& idProvider) :
		IObjectRepository(idProvider)
	{}

	~SceneFactory();

	void clear();

	int addWireFrameScene(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	int addPolygonMeshScene(Shape::PolygonMesh* mesh, const std::string& name);

	PolygonMeshScene* findObjectById(const int id) const;

	std::list<WireFrameScene*> getWires() const { return wires; }

	std::list<PolygonMeshScene*> getObjects() const { return polygonMeshes; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	std::list<WireFrameScene*> wires;
	std::list<PolygonMeshScene*> polygonMeshes;
};

	}
}