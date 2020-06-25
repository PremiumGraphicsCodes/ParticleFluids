#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include <array>
#include <list>

namespace Crystal {
	namespace Shape {
		class IPoint;
	}
	namespace Physics {

class UniformGrid3d : private UnCopyable
{
public:
	UniformGrid3d(const double divideLength, const Math::Vector3dd& min);

	void add(Shape::IPoint* particle);

	//void getNeighbors(MicroParticle* micro);

private:
	std::array<std::array<std::array<std::list<Shape::IPoint*>, 128>,128>, 128> grid;

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const double divideLength;
};

	}
}