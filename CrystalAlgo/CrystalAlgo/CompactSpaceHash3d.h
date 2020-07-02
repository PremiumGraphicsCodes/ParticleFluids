#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include "ZOrderCurve3d.h"
#include <list>
#include <functional>

namespace Crystal {
	namespace Shape {
		class IPoint;
	}
	namespace Search {

class CompactSpaceCell
{
public:
	unsigned int cellId;
	std::vector<Shape::IPoint*> particles;
};

class CompactSpaceHash3d : private UnCopyable
{
public:
	CompactSpaceHash3d(const double divideLength, const int tableSize);

	~CompactSpaceHash3d();

	void clear();

	//void add(const Shape::IParticleSystem& particles);

	void add(Shape::IPoint* particle);

	void solveInteractions(Shape::IPoint* particle, const std::function<void(Shape::IPoint*, Shape::IPoint*)>& func);

private:
	std::vector<std::vector<CompactSpaceCell*>> table;

	std::vector<CompactSpaceCell*> cells;

	unsigned int toHash(const Math::Vector3df& pos) const;

	unsigned int toHash(const std::array<unsigned int, 3>& index) const;

	std::array<unsigned int, 3> toIndex(const Math::Vector3df& pos) const;

	unsigned int toZIndex(const std::array<unsigned int, 3>& index) const;

	const double divideLength;
	
	const ZOrderCurve3d zCurve;
};

	}
}