#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Ray3d.h"

namespace Crystal {
	namespace Algo {

class IntersectionAlgo
{
public:
	void calculateIntersection(const Math::Ray3d& ray, const Math::Triangle3d& triangle);

	void calculateIntersection(const Math::Triangle3d& lhs, const Math::Triangle3d& rhs);

private:
	std::vector<Math::Vector3dd> intersections;
};
	}
}