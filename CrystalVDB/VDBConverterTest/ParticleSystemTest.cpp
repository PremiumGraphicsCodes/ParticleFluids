#include "gtest/gtest.h"

#include "../VDBConverter/VDBParticleSystem.h"

#include "../../Crystal/Shape/ParticleSystem.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(VDBParticleSystemTest, TestFromCrystal)
{
	std::vector<Vector3dd> ps;
	ps.push_back(Vector3dd(0, 0, 0));
	ps.push_back(Vector3dd(1, 2, 3));

	VDBParticleSystem dest;
	dest.fromCrystal(ps, 2.0f);

	EXPECT_EQ(Vector3dd(0,0,0), dest.getPosition(0));
	EXPECT_EQ(Vector3dd(1,2,3), dest.getPosition(1));

	EXPECT_EQ(2.0f, dest.getSize(0));
	EXPECT_EQ(2.0f, dest.getSize(1));
}

TEST(VDBParticleSystemTest, TestToCrystal)
{
	VDBParticleSystem ps;
	ps.add(Vector3dd(0, 0, 0), 1.0);
	ps.add(Vector3dd(1, 2, 3), 2.0f);

	auto dest = ps.toCrystal();

	const auto actual = dest->getPositions();

	EXPECT_EQ(Vector3dd(0, 0, 0), actual[0]);
	EXPECT_EQ(Vector3dd(1, 2, 3), actual[1]);
}