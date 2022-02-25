#include "pch.h"
#include "../CrystalPhysics/MPS/MPSParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	std::vector<MPSParticle*> createTestParticles2d()
	{
		std::vector<MPSParticle*> particles;
		const auto length = 0.1;
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {
				const auto x = i * length;
				const auto y = j * length;
				const auto pos = Vector3df(x, y, 0.0f);
				auto p = new MPSParticle(pos);
				particles.emplace_back(p);
			}
		}
		for (auto p : particles) {
			if (p != particles[24]) {
				particles[24]->addNeighbor(p);
			}
		}
		//particles[24]->addNeighbor(particles);
		return particles;
	}
}

TEST(MPSParticleTest, TestCalculateNumberDensity)
{
	const auto ps = ::createTestParticles2d();
	// This expected data is from the book "—±Žq–@“ü–å"(in Japanese).
	ps[24]->calculateNumberDensity(0.21);
	const auto actual = ps[24]->getNumberDensity();
	const float expected = 6.539696;
	EXPECT_NEAR(expected, actual, 1.0e-5);

	for (auto p : ps) {
		delete p;
	}
}
