#include "PolygonMeshObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

PolygonMeshObjectRepository::~PolygonMeshObjectRepository()
{
	clear();
}

void PolygonMeshObjectRepository::clear()
{
	for (auto p : polygonMeshes) {
		delete p.getShape();
	}
	polygonMeshes.clear();
}

int PolygonMeshObjectRepository::addObject(PolygonMesh* mesh, const Material& material, const std::string& name)
{
	polygonMeshes.push_back(PolygonMeshObject(nextId++, name, mesh, material));
	return polygonMeshes.back().getId();
}

Box3d PolygonMeshObjectRepository::getBoundingBox() const
{
	const auto& vertices = getAllVertices();
	if (vertices.empty()) {
		return Box3d();
	}
	Box3d bb(vertices.front());
	for (const auto& v : vertices) {
		bb.add(v);
	}
	return bb;
}

std::list<Vector3dd> PolygonMeshObjectRepository::getAllVertices() const
{
	std::list<Vector3dd> positions;
	for (const auto& ps : polygonMeshes) {
		const auto& vs = ps.getShape()->getVertices();
		for (const auto& p : vs) {
			positions.push_back(p->getPosition());
		}
	}
	return positions;
}
