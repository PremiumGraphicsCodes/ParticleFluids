#include "SolverModel.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalPhysics/CrystalPhysics/Boundary/CSGBoundaryScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"


using namespace Crystal::Scene;
using namespace Crystal::UI;

using namespace PG::FS;

void SolverModel::init(World* world)
{
	auto ps = std::make_unique<Crystal::Shape::ParticleSystem<ParticleAttribute>>();
	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					auto p = Vector3dd(i * length, j * length, k * length);
					ParticleAttribute attr;
					attr.size = 0.25f;
					ps->add(p, attr);
				}
			}
		}
	}
	auto psScene = new ParticleSystemScene(world->getNextSceneId(), "", std::move(ps));
	psScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(psScene);


	auto fm = std::make_unique<PG::FS::FluidModel>();
	fm->create(world);

	auto fluidScene = world->getScenes()->findSceneById<MVPFluidScene*>(fm->fluidId);
	updator.add(fluidScene);


	fm->particleSystemId = psScene->getId();
	fluids.push_back(std::move(fm));

	/*
	auto emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "Emitter");
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 1; ++j) {
			for (int k = 0; k < 10; ++k) {
				emitterScene->addSource(Sphere3d(Vector3dd(i * 0.5, j * 0.5, k * 0.5), 0.5));
			}
		}

	emitterScene->setInitialTemperature(1000.0f);
	emitterScene->setLifeLimit(100);
	emitterScene->setInterval(2);
	emitterScene->setInitialVelocity(Vector3dd(0.0, 0.0, 0.0));
	emitterScene->setStartEnd(0, 10000);

	}
	*/

	//addStaticScene(staticScene);

	exporter = new SolverExporter(world);
	world->addAnimation(exporter);

	world->addAnimation(&solver);
	world->addAnimation(&updator);


	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");
}

void SolverModel::reset(World* world)
{
	solver.clear();
	//updator.

	for (auto& fm : fluids) {
		fm->reset(world);
		auto f = world->getScenes()->findSceneById<MVPFluidScene*>(fm->fluidId);
		if (f->isBoundary()) {
			solver.addBoundaryScene(f);
		}
		else {
			solver.addFluidScene(f);
		}
	}
}

void SolverModel::addFluid(World* world)
{
	auto fm = std::make_unique<PG::FS::FluidModel>();
	fm->create(world);
	fluids.push_back(std::move(fm));
}

void SolverModel::addEmitter(World* world)
{
	auto fm = std::make_unique<PG::FS::EmitterModel>();
	fm->create(world);
	emitters.push_back(std::move(fm));
}
