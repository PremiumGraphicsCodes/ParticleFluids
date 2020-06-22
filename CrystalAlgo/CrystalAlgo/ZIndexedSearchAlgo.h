#pragma once

#include "../../Crystal/Math/Vector3d.h"

#include "../../Crystal/Util/UnCopyable.h"

#include "ZOrderCurve3d.h"

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
	ZIndexedParticle(const unsigned int zIndex, Shape::IPoint* point) :
		zIndex(zIndex),
		point(point)
	{}

	bool operator<(const ZIndexedParticle& rhs) const {
		return this->zIndex < rhs.zIndex;
	}

	/*
	bool operator==(const ZIndexedParticle& rhs) {
		return this->zIndex == rhs.zIndex;
	}
	*/

	Shape::IPoint* getPoint() { return point; }

private:
	unsigned int zIndex;
	Shape::IPoint* point;
};

class ZIndexedSearchAlgo : private UnCopyable
{
public:
	explicit ZIndexedSearchAlgo(const double searchRadius, const Math::Vector3dd& minPosition);

	void add(Shape::IPoint* point);

	void sort();

	std::list<Shape::IPoint*> findNeighbors(const Math::Vector3dd& position);

	std::array<unsigned int, 3> toIndex(const Math::Vector3dd& position) const;

private:
	double searchRadius;
	Math::Vector3dd minPosition;
	std::list<ZIndexedParticle> points;
	ZOrderCurve3d curve;
};
	}
}