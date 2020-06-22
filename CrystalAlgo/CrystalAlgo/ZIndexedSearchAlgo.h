#pragma once

#include "../../Crystal/Math/Vector3d.h"

#include "../../Crystal/Util/UnCopyable.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Shape {
		class IPoint;
	}
	namespace Search {

class ZIndexedParticle
{
public:
	ZIndexedParticle(const int zIndex, Shape::IPoint* point) :
		zIndex(zIndex),
		point(point)
	{}

	bool operator<(const ZIndexedParticle& rhs) {
		return this->zIndex < rhs.zIndex;
	}

private:
	int zIndex;
	Shape::IPoint* point;
};

class ZIndexedSearchAlgo : private UnCopyable
{
public:
	explicit ZIndexedSearchAlgo(const double searchRadius);

	void add(Shape::IPoint* point);

	void sort();

	std::list<Shape::IPoint*> findNeighbors(Shape::IPoint* searchPoint);

	std::array<unsigned int, 3> toIndex(const Math::Vector3dd& position) const;

private:
	double searchRadius;
	std::list<ZIndexedParticle> points;
};
	}
}