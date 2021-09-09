#include "IntersectionAlgo.h"

#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Math/Plane3d.h"
#include "../../Crystal/Math/Quad3d.h"
#include "../../Crystal/Math/Box3d.h"

#include "../../Crystal/Shape/PolygonMesh.h"

//#define GLM_ENABLE_EXPERIMENTAL
//#include "../../Crystal/ThirdParty/glm-0.9.9.3/glm/gtx/intersect.hpp"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Sphere3dd& sphere, const double tolerance)
{
	const auto& direction = ray.getDirection();
	const auto& diff = sphere.getCenter() - ray.getOrigin();
	const auto t0 = glm::dot(diff, direction);
	const auto distanceSquared = glm::dot(diff, diff) - t0 * t0;
	const auto sphereRadiusSquared = sphere.getRadius() * sphere.getRadius();
	if (distanceSquared > sphereRadiusSquared)
	{
		return false;
	}
	const auto t1 = std::sqrt(sphereRadiusSquared - distanceSquared);
	const auto intersectionDistance = t0 > t1 + tolerance ? t0 - t1 : t0 + t1;
	if (intersectionDistance > tolerance) {
		const auto& i = ray.getPosition(intersectionDistance);
		const auto& normal = glm::normalize( i - sphere.getCenter() );
		intersections.push_back(Intersection(i, normal));
		return true;
	}
	return false;
}

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Sphere3dd& sphere, const double tolerance)
{
	const auto& dir = glm::normalize(line.getDirection());
	const auto diff = sphere.getCenter() - line.getStart();
	const auto t0 = glm::dot(diff, dir);
	const auto dSquared = dot(diff, diff) - t0 * t0;
	const auto sphereRadiusSquared = sphere.getRadius() * sphere.getRadius();
	if (dSquared > sphereRadiusSquared)
	{
		return false;
	}
	auto t1 = sqrt(sphereRadiusSquared - dSquared);
	if (t0 < t1 + tolerance) {
		t1 = -t1;
	}
	Intersection i1;
	i1.position = line.getStart() + dir * (t0 - t1);
	i1.normal = glm::normalize(i1.position - sphere.getCenter());
	intersections.push_back(i1);
	Intersection i2;
	i2.position = line.getStart() + dir * (t0 + t1);
	i2.normal = glm::normalize(i2.position - sphere.getCenter());
	intersections.push_back(i2);
	return true;
}

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Triangle3d& triangle, const double tolerance)
{
	const auto& plane = triangle.toPlane();

	IntersectionAlgo innerAlgo;
	if (!innerAlgo.calculateIntersection(line, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (triangle.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = triangle.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Quad3d& quad, const double tolerance)
{
	const auto& plane = quad.toPlane();

	IntersectionAlgo innerAlgo;
	if (!innerAlgo.calculateIntersection(line, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (quad.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = quad.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Quad3d& quad, const double tolerance)
{
	const auto& plane = quad.toPlane();

	IntersectionAlgo innerAlgo;
	if (!innerAlgo.calculateIntersection(ray, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (quad.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = quad.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Plane3d& plane, const double tolerance)
{
	const auto distance = plane.getDistance(ray.getOrigin());

	if (distance > -tolerance)
	{
		const Intersection intersection(ray.getPosition(distance), plane.getNormal());
		intersections.push_back(intersection);
		return true;
	}
	return false;
}

bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Triangle3d& triangle, const double tolerance)
{
	const auto& normal = triangle.getNormal();
	IntersectionAlgo innerAlgo;
	const Plane3d plane(triangle.getVertices()[0], triangle.getNormal());
	if (!innerAlgo.calculateIntersection(ray, plane, tolerance)) {
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

// ref https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool IntersectionAlgo::calculateIntersection(const Ray3d& ray, const Box3dd& box, const double tolerance)
{
	// tmin, tmax -> parameter

	const auto origin = ray.getOrigin();
	const auto dir = ray.getDirection();

	const auto min = box.getMin();
	const auto max = box.getMax();
	float tmin = (min.x - origin.x) / dir.x;
	float tmax = (max.x - origin.x) / dir.x;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (min.y - origin.y) / dir.y;
	float tymax = (max.y - origin.y) / dir.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (min.z - origin.z) / dir.z;
	float tzmax = (max.z - origin.z) / dir.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	intersections.push_back( Intersection( ray.getPosition(tmin), Vector3dd() ));
	intersections.push_back(Intersection(ray.getPosition(tmax), Vector3dd()));

	return true;
}

bool IntersectionAlgo::calculateIntersection(const Line3dd& line, const Plane3d& plane, const double tolerance)
{
	// 線分の始点が三角系の裏側にあれば、当たらない
	const auto planeToStart = plane.getDistance(line.getStart());	// 線分の始点と平面の距離
	if (planeToStart <= tolerance) {
		return false;
	}

	// 線分の終点が三角系の表側にあれば、当たらない
	const auto planeToEnd = plane.getDistance(line.getEnd());	// 線分の終点と平面の距離
	if (planeToEnd >= -tolerance) {
		return false;
	}

	// 直線と平面との交点を取る
	const auto denom = planeToStart - planeToEnd;
	const auto param = planeToStart / denom;

	Intersection i(line.getPosition(param), plane.getNormal());
	intersections.push_back(i);
	return true;
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

bool IntersectionAlgo::calculateIntersection(const PolygonMesh& lhs, const PolygonMesh& rhs, const double tolerance)
{
	/*
	const auto& faces1 = lhs.getFaces();
	std::vector<Triangle3d> triangles1;
	for (auto f : faces1) {
		const auto& triangle = f->toTriangle();
		triangles1.push_back(triangle);
	}
	const auto& faces2 = rhs.getFaces();
	std::vector<Triangle3d> triangles2;
	for (auto f : faces2) {
		const auto& triangle = f->toTriangle();
		triangles2.push_back(triangle);
	}
	for (const auto& t1 : triangles1) {
		for (const auto& t2 : triangles2) {
			calculateIntersection(t1, t2, tolerance);
		}
	}
	*/
	return !intersections.empty();
}