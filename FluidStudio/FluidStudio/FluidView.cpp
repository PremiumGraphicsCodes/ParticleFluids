#include "FluidView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

FluidView::FluidView(const std::string& name, World* world, Canvas* canvas, MainModel* mainModel) :
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

void FluidView::onOk()
{
	auto world = getWorld();
	auto fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");

	fluidScene->setPressureCoe(pressureCoeView.getValue());
	fluidScene->setViscosityCoe(viscosityCoeView.getValue());
	fluidScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	fluidScene->setDragForceCoe(dragForceCoeView.getValue());
	fluidScene->setDragHeatCoe(dragHeatCoeView.getValue());

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

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

	staticScene->setPressureCoe(pressureCoeView.getValue());
	staticScene->setViscosityCoe(viscosityCoeView.getValue() * 5.0f);
	staticScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

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

	fluidScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(fluidScene);
	model->addFluidScene(fluidScene);

	staticScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(staticScene);
	model->addStaticScene(staticScene);
}