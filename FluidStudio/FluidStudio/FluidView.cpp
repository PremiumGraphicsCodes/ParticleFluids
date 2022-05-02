#include "FluidView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

FluidView::FluidView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
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

void FluidView::setValue(MVPFluidScene* fluid)
{
	this->fluidScene = fluid;

	this->pressureCoeView.setValue(fluid->getPressure());
	this->viscosityCoeView.setValue(fluid->getViscosityCoe());
	this->heatDiffuseCoeView.setValue(fluid->getHeatDiffuseCoe());
	this->dragForceCoeView.setValue(fluid->getDragForceCoe());
	this->dragHeatCoeView.setValue(fluid->getDragHeatCoe());
}

void FluidView::onOk()
{
	fluidScene->setPressureCoe(pressureCoeView.getValue());
	fluidScene->setViscosityCoe(viscosityCoeView.getValue());
	fluidScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	fluidScene->setDragForceCoe(dragForceCoeView.getValue());
	fluidScene->setDragHeatCoe(dragHeatCoeView.getValue());
}