#pragma once

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Algo {

class BooleanAlgo
{
public:
	explicit BooleanAlgo( Shape::PolygonMeshBuilder* builder ) :
		builder(builder)
	{}

	void calculateUnion(const Shape::PolygonMesh& lhs, const Shape::PolygonMesh& rhs);

	void calculateDifference(const Shape::PolygonMesh& lhs, const Shape::PolygonMesh& rhs);

	void calculateIntersection(const Shape::PolygonMesh& lhs, const Shape::PolygonMesh& rhs);

	Shape::PolygonMesh* getResult() { return result; }

private:
	Shape::PolygonMeshBuilder* builder;
	Shape::PolygonMesh* result;
};
	}
}