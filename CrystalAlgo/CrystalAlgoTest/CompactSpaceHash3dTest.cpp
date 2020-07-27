#include "gtest/gtest.h"

#include "../CrystalAlgo/CompactSpaceHash3d.h"

#include "../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;

class TestPoint : public IParticle
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

	TestPoint point1(Vector3dd(1,1,1));
	TestPoint point2(Vector3dd(1,1,1));
	spaceHash.add(&point1);
	spaceHash.add(&point2);
	const auto neighbors = spaceHash.findNeighbors(&point1);
	EXPECT_EQ(1, neighbors.size());
}