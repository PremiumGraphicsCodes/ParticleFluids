#include "gtest/gtest.h"

#include "../VDBConverter/ParticleSystem.h"

#include "../../Crystal/Shape/ParticleSystem.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(ParticleSystemTest, TestToCrystal)
{
	Crystal::Shape::ParticleSystem<Crystal::Shape::IParticleAttribute> ps;
	ps.add(Vector3dd(0, 0, 0), Crystal::Shape::IParticleAttribute(1.0f));
	ps.add(Vector3dd(1, 2, 3), Crystal::Shape::IParticleAttribute(2.0f));

	ParticleSystem dest;
	dest.fromCrystal(ps);

	EXPECT_EQ(Vector3dd(0,0,0), dest.getPosition(0));
	EXPECT_EQ(Vector3dd(1,2,3), dest.getPosition(1));

	EXPECT_EQ(1.0f, dest.getSize(0));
	EXPECT_EQ(2.0f, dest.getSize(1));

}