#include "MainModel.h"

#include "CrystalPhysics/CrystalPhysics/Boundary/CSGBoundaryScene.h"

using namespace Crystal::UI;

void MainModel::init()
{
	auto fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");

	fluidScene->setPressureCoe(500.0);

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	/*
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
	*/

	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = fluidScene->create(p, length, 0.25f, 300.0f);
					//				mp->distributePoints(3, 3, 3, 1.00f);
					fluidScene->addParticle(mp);
				}
			}
		}
	}

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


	fluidScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(fluidScene);
	addFluidScene(fluidScene);

	staticScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(staticScene);
	addStaticScene(staticScene);

	exporter = new SolverExporter(world);
	world->addAnimation(exporter);

	world->addAnimation(&solver);
	world->addAnimation(&updator);

	updator.add(fluidScene);
	updator.add(staticScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");
}

void MainModel::resetSolver()
{
	solver.clear();
	//updator.

	for (auto f : fluidScenes) {
		solver.addFluidScene(f);
	}
	
	for (auto s : staticScenes) {
		solver.addBoundaryScene(s);
	}
}
