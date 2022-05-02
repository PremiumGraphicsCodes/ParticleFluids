#include "EmitterView.h"

using namespace Crystal::UI;

EmitterView::EmitterView(const std::string& name, World* world, Canvas* canvas, MainModel* mainModel) :
	IOkCancelView(name, world, canvas),
	model(mainModel),
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	heatDiffuseCoeView("HeatDiffuseCoe", 100.0f),
	dragHeatCoeView("DragHeatCoe", 0.0),
	dragForceCoeView("DragForceCoe", 0.0)
{
	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&heatDiffuseCoeView);
	add(&dragHeatCoeView);
	add(&dragForceCoeView);
}

void EmitterView::onOk()
{
	auto world = getWorld();
	auto emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");

	emitterScene->setPressureCoe(pressureCoeView.getValue());
	emitterScene->setViscosityCoe(viscosityCoeView.getValue());
	emitterScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	emitterScene->setDragForceCoe(dragForceCoeView.getValue());
	emitterScene->setDragHeatCoe(dragHeatCoeView.getValue());

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 1; ++j) {
			for (int k = 0; k < 10; ++k) {
				emitterScene->addSource(Sphere3d(Vector3dd(i * 0.5, j * 0.5, k * 0.5), 0.5));
			}
		}
	}
	emitterScene->setInitialTemperature(1000.0f);
	emitterScene->setLifeLimit(100);
	emitterScene->setInterval(2);
	emitterScene->setInitialVelocity(Vector3dd(0.0, 0.0, 0.0));
	emitterScene->setStartEnd(0, 10000);

	emitterScene->getPresenter()->createView(world->getRenderer());

	world->getScenes()->addScene(emitterScene);


	model->addEmitterScene(emitterScene);
	model->solver.addEmitterScene(emitterScene);
}