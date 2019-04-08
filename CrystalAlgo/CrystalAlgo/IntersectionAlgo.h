#pragma once

#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Math {
		class Line3dd;
		class Sphere3d;
		class Ray3d;
		class Plane3d;
		class Triangle3d;
		class Quad3d;
	}
	namespace Algo {

struct Intersection
{
public:
	Intersection() :
		position(0,0,0),
		normal(0,0,1)
	{
	}

	Intersection(const Math::Vector3dd& position, const Math::Vector3dd& normal) :
		position(position),
		normal(normal)
	{}

	Math::Vector3dd position;
	Math::Vector3dd normal;
};

class IntersectionAlgo
{
public:
	bool calculateIntersection(const Math::Ray3d& ray, const Math::Sphere3d& sphere, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Plane3d& plane, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Triangle3d& triangle, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Quad3d& quad, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Plane3d& plane, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Sphere3d& sphere, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Triangle3d& triangle, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Quad3d& quad, const double tolerance);

	bool calculateIntersection(const Math::Triangle3d& lhs, const Math::Triangle3d& rhs, const double tolerance);

	std::vector<Intersection> getIntersections() const { return intersections; }

private:
	std::vector<Intersection> intersections;
};
	}
}