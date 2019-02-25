#include "gtest/gtest.h"

#include "../Math/Sphere3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;

TEST(Sphere3dTest, OffsetTest)
{
	Sphere3d s;
	s.outerOffset(1.0f);
	EXPECT_EQ(2.0f, s.getRadius());

	s.innerOffset(1.0f);
	EXPECT_EQ(1.0f, s.getRadius());
}

TEST(Sphere3dTest, TestIsInner)
{
	const Sphere3d s(Vector3df(0.0, 0.0, 0.0), 1.0f);
	EXPECT_TRUE(s.isInner(Vector3df(0.0f, 0.0f, 0.0f)));
	EXPECT_FALSE(s.isInner(Vector3df(2.0f, 0.0f, 0.0f)));
}

TEST(Sphere3dTest, TestGetPosition)
{
	const auto tolerance = 1.0e-12;

	const Sphere3d s(Vector3dd(0.0, 0.0, 0.0), 1.0);
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition(0.0, 0.0 ), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition(0.0, 0.25), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition(0.0, 0.5 ), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition(0.0, 0.75), tolerance) );
	EXPECT_TRUE( areSame( Vector3dd( 0, 0, 1), s.getPosition(0.0, 1.0 ), tolerance) );

	EXPECT_TRUE(areSame(Vector3dd( 1, 0, 0), s.getPosition(0.5, 0.0 ), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 0, 1, 0), s.getPosition(0.5, 0.25), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(-1, 0, 0), s.getPosition(0.5, 0.5 ), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 0,-1, 0), s.getPosition(0.5, 0.75), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 1, 0, 0), s.getPosition(0.5, 1.0 ), tolerance));

	EXPECT_TRUE(areSame(Vector3dd( 0, 0,-1), s.getPosition(1.0, 0.0 ), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 0, 0,-1), s.getPosition(1.0, 0.25), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 0, 0,-1), s.getPosition(1.0, 0.5 ), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 0, 0,-1), s.getPosition(1.0, 0.75), tolerance));
	EXPECT_TRUE(areSame(Vector3dd( 0, 0,-1), s.getPosition(1.0, 1.0 ), tolerance));
}

TEST(Sphere3dTest, TestGetNormal)
{
	const auto tolerance = 1.0e-12;

	const Sphere3d s(Vector3dd(0.0, 0.0, 0.0), 1.0);

	EXPECT_TRUE(areSame(Vector3dd(0, 0, 1), s.getNormal(0.0, 0.0), tolerance));
	EXPECT_TRUE(areSame(Vector3dd(1, 0, 0), s.getNormal(0.5, 0.0), tolerance));
}