#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"

namespace Crystal {
	namespace Algo {

class SpaceHash
{
public:
	SpaceHash(const float divideLength, const int tableSize);

	//void add(Shape::Partic particleSystem);

	int toHash(const Math::Vector3df& pos);

	int toHash(const std::array<int,3>& index);

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const float divideLength;

	const long int p1 = 73856093;
	const long int p2 = 19349663;
	const long int p3 = 83492791;
	const int tableSize;
};
	}
}