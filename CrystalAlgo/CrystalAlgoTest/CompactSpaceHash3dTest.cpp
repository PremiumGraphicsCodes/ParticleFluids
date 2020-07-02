#include "gtest/gtest.h"

#include "../CrystalAlgo/CompactSpaceHash3d.h"

#include "../../Crystal/Shape/IPoint.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;

class TestPoint : public IPoint
{
public:
	TestPoint(const Vector3dd& position) :
		position(position)
	{}

	Vector3dd getPosition() const override { return position; }

private:
	Vector3dd position;
};

TEST(CompactSpaceHash3dTest, TestSolveInteractions)
{
	CompactSpaceHash3d spaceHash(1.0, 10);

	unsigned int count = 0;
	auto func = [&count](IPoint* lhs, IPoint* rhs) {
		++count;
	};

	TestPoint point1(Vector3dd(1,1,1));
	TestPoint point2(Vector3dd(1,1,1));
	spaceHash.add(&point1);
	spaceHash.add(&point2);
	spaceHash.solveInteractions(&point1, func);
	EXPECT_EQ(1, count);
}