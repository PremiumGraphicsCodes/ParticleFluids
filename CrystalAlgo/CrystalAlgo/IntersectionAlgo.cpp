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

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Triangle3d& triangle, const double tolerance)
{
	const auto& origin = triangle.getVertices()[0];
	const auto& normal = triangle.getNormal();

	// 線分の始点が三角系の裏側にあれば、当たらない
	const auto tls = line.getStart() - origin;
	const auto distl0 = glm::dot( tls , normal);	// 線分の始点と平面の距離
	if (distl0 <= tolerance) {
		return false;
	}

	// 線分の終点が三角系の表側にあれば、当たらない
	const auto tle = line.getEnd() - origin;
	const auto distl1 = glm::dot( tle, normal);	// 線分の終点と平面の距離
	if (distl1 >= -tolerance) {
		return false;
	}

	// 直線と平面との交点sを取る
	const auto denom = distl0 - distl1;
	const auto t = distl0 / denom;

	const auto s = t * line.getDirection() + line.getStart();

	if (triangle.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = triangle.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
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
	const auto& normal = triangle.getNormal();
	IntersectionAlgo innerAlgo;
	const Plane3d plane(triangle.getVertices()[0], triangle.getNormal());
	if (!innerAlgo.calculateIntersection(ray, plane)) {
		return false;
	}
	const auto intersectionOnPlane = innerAlgo.getIntersections()[0];

	const auto& i = intersectionOnPlane.position;
	if (triangle.isInside(i)) {
		intersections.push_back(intersectionOnPlane);
		return true;
	}
	return false;
}

bool IntersectionAlgo::calculateIntersection(const Triangle3d& lhs, const Triangle3d& rhs, const double tolerance)
{
	const auto& vertices = lhs.getVertices();
	const auto l1 = Line3dd::fromPoints(vertices[0], vertices[1]);
	const auto l2 = Line3dd::fromPoints(vertices[1], vertices[2]);
	const auto l3 = Line3dd::fromPoints(vertices[2], vertices[0]);
	const auto found1 = calculateIntersection(l1, rhs, tolerance);
	const auto found2 = calculateIntersection(l2, rhs, tolerance);
	const auto found3 = calculateIntersection(l3, rhs, tolerance);
	return (found1 || found2 || found3);
}
