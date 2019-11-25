#pragma once


namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Algo {

class BooleanAlgo
{
public:
	void calculateUnion(const Shape::PolygonMesh& lhs, const Shape::PolygonMesh& rhs);

	void calculateDifference(const Shape::PolygonMesh& lhs, const Shape::PolygonMesh& rhs);

	void calculateIntersection(const Shape::PolygonMesh& lhs, const Shape::PolygonMesh& rhs);

	Shape::PolygonMesh* getResult() { return result; }

private:
	Shape::PolygonMesh* result;
};
	}
}