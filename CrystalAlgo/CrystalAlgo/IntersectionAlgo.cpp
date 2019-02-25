#include "IntersectionAlgo.h"

#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Math/Plane3d.h"

#include "../../Crystal/Math/Matrix3d.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "../../Crystal/ThirdParty/glm-0.9.9.3/glm/gtx/intersect.hpp"

using namespace Crystal::Math;
using namespace Crystal::Algo;

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Sphere3d& sphere)
{
	const auto& start = line.getStart();
	const auto& end = line.getEnd();
	const auto radius = sphere.getRadius();
	const auto& center = sphere.getCenter();
	Intersection intersection;
	const auto found = glm::intersectLineSphere(start, end, center, radius, intersection.position, intersection.normal);
	if (found) {
		intersections.push_back(intersection);
	}
	return found;
}

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Triangle3d& triangle)
{
	const auto& start = line.getStart();
	const auto& direction = line.getDirection();

	const auto& vertices = triangle.getVertices();
	const auto& v0 = vertices[0];
	const auto& v1 = vertices[1];
	const auto& v2 = vertices[2];

	Intersection intersection;
	const auto found = glm::intersectLineTriangle(start, direction, v0, v1, v2, intersection.position);
	if (found) {
		intersection.normal = triangle.getNormal();
		intersections.push_back(intersection);
	}
	return found;
}

bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Plane3d& plane)
{
	const auto& origin = ray.getOrigin();
	const auto& direction = ray.getDirection();
	double distance = 0.0;
	const auto found = glm::intersectRayPlane(origin, direction, plane.getOrigin(), plane.getNormal(), distance);
	if (found) {
		const Intersection intersection( origin + direction * distance, plane.getNormal());
		intersections.push_back(intersection);
	}
	return found;
}

bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Triangle3d& triangle)
{
	const auto& vertices = triangle.getVertices();
	const auto& v0 = vertices[0];
	const auto& v1 = vertices[1];
	const auto& v2 = vertices[2];
	const auto edge1 = v1 - v0;
	const auto edge2 = v2 - v0;

	const auto& origin = ray.getOrigin();
	const auto& direction = ray.getDirection();

	const Matrix3dd matrix(v1, v2, -direction);
	const auto denominator = glm::determinant(matrix);

	if (denominator > 0.0) {
		const Matrix3dd matrixu(origin - v0, edge2, -direction);
		const auto u = glm::determinant(matrixu) / denominator;
		if (0.0 <= u && u <= 1.0) {
			const Matrix3dd matrixv(edge1, origin - v0, -direction);
			const auto v = glm::determinant(matrixv) / denominator;
			if (0.0 <= v && v <= 1.0) {
				const Matrix3dd matrixt(edge1, edge2, origin - v0);
				const auto t = glm::determinant(matrixt) / denominator;
				const Intersection intersection( origin + direction * t, triangle.getNormal());
				intersections.push_back(intersection);
				return true;
			}
		}
	}
	return false;
}

/*
bool IntersectionAlgo::calculateIntersection(const Triangle3d& lhs, const Triangle3d& rhs)
{
	return false;
}
*/
