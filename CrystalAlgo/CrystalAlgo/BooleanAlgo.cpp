#include "BooleanAlgo.h"

#include "../../Crystal/Scene/PolygonMesh.h"
#include "../../Crystal/Scene/PolygonMeshBuilder.h"

#define CSGJS_HEADER_ONLY
#include "csgjs.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Algo;

namespace {
	csgjs_model toCSGJSModel(const PolygonMesh& polygon)
	{
		csgjs_model model;
		const auto& vertices = polygon.getVertices();
		/*
		for (auto vv : vertices) {
			const auto& pos = vv->getPosition();
			const auto& normal = vv->getNormal();

			csgjs_vertex v;
			v.pos = csgjs_vector(pos.x, pos.y, pos.z);
			v.normal = csgjs_vector(normal.x, normal.y, normal.z);
			model.vertices.push_back(v);
		}
		*/

		/*
		const auto& faces = polygon.getFaceG();
		for (auto f : faces) {
			model.indices.push_back(f->getV1()->getAttr().id);
			model.indices.push_back(f->getV2()->getAttr().id);
			model.indices.push_back(f->getV3()->getAttr().id);
		}
		*/
		return model;
	}

	PolygonMesh* fromCSGJSModel(const csgjs_model& model)
	{
		/*
		Crystal::Shape::VertexFactory vertexFactory;
		Crystal::Shape::PolygonMeshBuilder builder;
		std::vector<std::pair<Vector3dd, Vector3dd> > vs;
		for (const auto& v : model.vertices) {
			const Vector3dd p(v.pos.x, v.pos.y, v.pos.z);
			const Vector3dd n(v.normal.x, v.normal.y, v.normal.z);
			vertexFactory.createVertex(p, n);
		}
		builder.build(model.indices);
		return builder.getPolygonMesh();
		*/
		return nullptr;
	}
}

void BooleanAlgo::calculateUnion(const PolygonMesh& lhs, const PolygonMesh& rhs)
{
	const auto& result = csgjs_union(toCSGJSModel(lhs), toCSGJSModel(rhs));
	this->result = fromCSGJSModel(result);
}

void BooleanAlgo::calculateDifference(const PolygonMesh& lhs, const PolygonMesh& rhs)
{
	const auto& result = csgjs_difference(toCSGJSModel(lhs), toCSGJSModel(rhs));
	this->result = fromCSGJSModel(result);
}

void BooleanAlgo::calculateIntersection(const PolygonMesh& lhs, const PolygonMesh& rhs)
{
	const auto& result = csgjs_intersection(toCSGJSModel(lhs), toCSGJSModel(rhs));
	this->result = fromCSGJSModel(result);
}

/*
PolygonMesh getResult() const
{

}
*/
