#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include <array>
#include <list>
#include <functional>

namespace Crystal {
	namespace Shape {
		class IPoint;
	}
	namespace Search {

class UniformGrid3d : private UnCopyable
{
public:
	UniformGrid3d(const double divideLength, const Math::Vector3dd& min);

	void add(Shape::IPoint* particle);

	void solveInteractions(Shape::IPoint* micro, const std::function<void(Shape::IPoint*, Shape::IPoint*)>& func);

private:
	std::array<std::array<std::array<std::list<Shape::IPoint*>, 128>, 128>, 128> grid;

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const double divideLength;
};

	}
}