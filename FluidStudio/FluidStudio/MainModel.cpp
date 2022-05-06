#include "MainModel.h"

#include "CrystalPhysics/CrystalPhysics/Boundary/CSGBoundaryScene.h"

using namespace Crystal::UI;

void MainModel::init()
{

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	/*
	*/

	FluidModel fm;
	fm.create(world);
	fluids.push_back(fm);

	auto staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");

	staticScene->setPressureCoe(500.0);

	//staticScene->setPressureCoe(pressureCoeView.getValue());
	//staticScene->setViscosityCoe(viscosityCoeView.getValue() * 5.0f);
	//staticScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = -10; i < 10; ++i) {
			for (int j = -1; j < 0; ++j) {
				for (int k = -10; k < 10; ++k) {
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = staticScene->create(p, length, 0.25f, 2000.0f);
					staticScene->addParticle(mp);
					staticScene->setBoundary(true);
				}
			}
		}

	}
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


	staticScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(staticScene);
	addStaticScene(staticScene);

	exporter = new SolverExporter(world);
	world->addAnimation(exporter);

	world->addAnimation(&solver);
	world->addAnimation(&updator);

	auto fluidScene = world->getScenes()->findSceneById<MVPFluidScene*>(fm.getFluidId());
	updator.add(fluidScene);
	updator.add(staticScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");
}

void MainModel::resetSolver()
{
	solver.clear();
	//updator.

	for (auto fm : fluids) {
		fm.reset(world);
		auto f = world->getScenes()->findSceneById<MVPFluidScene*>(fm.getFluidId());
		solver.addFluidScene(f);
	}
	
	for (auto s : staticScenes) {
		solver.addBoundaryScene(s);
	}
}
