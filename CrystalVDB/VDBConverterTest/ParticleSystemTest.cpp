#include "gtest/gtest.h"

#include "../VDBConverter/ParticleSystem.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(ParticleSystemTest, TestToCrystal)
{
	auto shape = std::make_unique< Crystal::Shape::ParticleSystem<Crystal::Scene::ParticleAttribute> >();
	shape->add(Vector3dd(0, 0, 0), Crystal::Scene::ParticleAttribute());
	Crystal::Scene::ParticleSystemScene scene(0, "", std::move(shape));

	ParticleSystem ps;
	ps.fromCrystal(scene);
}