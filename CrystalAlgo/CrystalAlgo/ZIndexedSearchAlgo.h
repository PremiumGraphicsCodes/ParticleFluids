#pragma once

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

class ZIndexedSearchAlgo
{
public:
	explicit ZIndexedSearchAlgo(const double searchRadius);

	void add(Shape::IPoint* point);

	void sort();

	int toIndex1d(unsigned int x, unsigned int y, unsigned int z);

	//std::list<Shape::IPoint*> findNeighbors(Shape::IPoint* searchPoint);

private:
	double searchRadius;
	std::vector<ZIndexedParticle> points;
};
	}
}