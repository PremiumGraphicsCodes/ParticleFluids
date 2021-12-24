#include "gtest/gtest.h"

#include "Crystal/Shape/Particle.h"
#include "CrystalSpace/CrystalSpace/DynamicOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

TEST(DynamicOctreeTest, TestDivide)
{
	Particle<float> p(Vector3dd(1,1,1), 1.0f);
	DynamicOctree octree(Box3dd(Vector3dd(0,0,0), Vector3dd(10,10,10)));
	octree.add(&p);
	octree.divide(1.0, { &p });
}