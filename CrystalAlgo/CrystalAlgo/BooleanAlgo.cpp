#include "BooleanAlgo.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#define CSGJS_HEADER_ONLY
#include "csgjs.h"

using namespace Crystal::Shape;
using namespace Crystal::Algo;

namespace {
	csgjs_model toCSGJSModel(const PolygonMesh& polygon)
	{
		csgjs_model model;
		const auto& vertices = polygon.getVertices();
		for (auto vv : vertices) {
			const auto& pos = vv->getPosition();
			const auto& normal = vv->getNormal();

			csgjs_vertex v;
			v.pos = csgjs_vector(pos.x, pos.y, pos.z);
			v.normal = csgjs_vector(normal.x, normal.y, normal.z);
			model.vertices.push_back(v);
		}

		const auto& faces = polygon.getFaces();
		for (auto f : faces) {
			model.indices.push_back(f->getV1()->getAttr().id);
			model.indices.push_back(f->getV2()->getAttr().id);
			model.indices.push_back(f->getV3()->getAttr().id);
		}
		return model;
	}

	/*
	PolygonMesh fromCSGJSModel(const csgjs_model& model)
	{
		PolygonMeshBuilder builder;
		builder.build()
		//PolygonMesh polygon;
		//polygon.a
	}
	*/
}

void BooleanAlgo::calculateUnion(const PolygonMesh& lhs, const PolygonMesh& rhs)
{
	csgjs_union(toCSGJSModel(lhs), toCSGJSModel(rhs));
}

void BooleanAlgo::calculateDifference(const PolygonMesh& lhs, const PolygonMesh& rhs)
{
	csgjs_difference(toCSGJSModel(lhs), toCSGJSModel(rhs));
}

void BooleanAlgo::calculateIntersection(const PolygonMesh& lhs, const PolygonMesh& rhs)
{
	csgjs_intersection(toCSGJSModel(lhs), toCSGJSModel(rhs));
}

/*
PolygonMesh getResult() const
{

}
*/
