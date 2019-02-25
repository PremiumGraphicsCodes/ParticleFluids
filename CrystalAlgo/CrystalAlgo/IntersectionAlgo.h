#pragma once

#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Math {
		class Line3dd;
		class Sphere3d;
		class Ray3d;
		class Triangle3d;
	}
	namespace Algo {

class IntersectionAlgo
{
public:
	bool calculateIntersection(const Math::Line3dd& line, const Math::Sphere3d& sphere);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Triangle3d& triangle);

	bool calculateIntersection(const Math::Triangle3d& lhs, const Math::Triangle3d& rhs);

private:
	std::vector<Math::Vector3dd> intersections;
};
	}
}