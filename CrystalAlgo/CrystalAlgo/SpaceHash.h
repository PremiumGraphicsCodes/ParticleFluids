#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"
#include <list>

namespace Crystal {
	namespace Algo {

class SpaceHash : private UnCopyable
{
public:
	SpaceHash(const float divideLength, const int tableSize);

	//void add(const Shape::IParticleSystem& particles);

	void add(Shape::IPoint* particle);

	std::list<Shape::IPoint*> getNeighbors(const Math::Vector3dd& position);

private:
	std::vector<std::list<Shape::IPoint*>> table;

	int toHash(const Math::Vector3df& pos);

	int toHash(const std::array<int, 3>& index);

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const float divideLength;


};
	}
}