#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include "ZOrderCurve3d.h"
#include <list>
#include <functional>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Space {

class CompactSpaceCell
{
public:
	unsigned int cellId;
	std::vector<Shape::IParticle*> particles;
};

class CompactSpaceHash3d : private UnCopyable
{
public:
	CompactSpaceHash3d();

	CompactSpaceHash3d(const double divideLength, const int tableSize);

	~CompactSpaceHash3d();

	void setup(const double divideLength, const int tableSize);

	void clear();

	//void add(const Shape::IParticleSystem& particles);

	void add(Shape::IParticle* particle);

	std::vector<Shape::IParticle*> findNeighbors(Shape::IParticle* particle);

	std::vector<Shape::IParticle*> findNeighbors(const Math::Vector3dd& position);

	void setCheckFunc(std::function<bool(Shape::IParticle*, Shape::IParticle*)> func) { this->checkFunc = func; }

private:
	std::vector<std::vector<CompactSpaceCell*>> table;

	std::vector<CompactSpaceCell*> cells;

	unsigned int toHash(const Math::Vector3df& pos) const;

	unsigned int toHash(const std::array<unsigned int, 3>& index) const;

	std::array<unsigned int, 3> toIndex(const Math::Vector3df& pos) const;

	unsigned int toZIndex(const std::array<unsigned int, 3>& index) const;

	double divideLength;
	
	ZOrderCurve3d zCurve;

	std::function<bool(Shape::IParticle* point1, Shape::IParticle* point2)> checkFunc;
};

	}
}