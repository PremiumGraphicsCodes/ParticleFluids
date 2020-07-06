#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include <list>
#include <functional>

namespace Crystal {
	namespace Shape {
		class IPoint;
	}
	namespace Search {

class SpaceHash3d : private UnCopyable
{
public:
	SpaceHash3d(const double divideLength, const int tableSize);

	//void add(const Shape::IParticleSystem& particles);

	void add(Shape::IPoint* particle);

	void solveInteractions(Shape::IPoint* particle, const std::function<void(Shape::IPoint*, Shape::IPoint*)>& func);

private:
	std::vector<std::list<Shape::IPoint*>> table;

	int toHash(const Math::Vector3df& pos);

	int toHash(const std::array<int, 3>& index);

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const double divideLength;
};

	}
}