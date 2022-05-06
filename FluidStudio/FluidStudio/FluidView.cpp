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

void FluidView::setValue(FluidModel* fluid)
{
	this->fluid = fluid;

	this->pressureCoeView.setValue(fluid->pressureCoe);
	this->viscosityCoeView.setValue(fluid->viscosityCoe);
	this->heatDiffuseCoeView.setValue(fluid->heatDiffuseCoe);
	this->dragForceCoeView.setValue(fluid->dragForceCoe);
	this->dragHeatCoeView.setValue(fluid->dragHeatCoe);
}

void FluidView::onOk()
{
	fluid->pressureCoe = pressureCoeView.getValue();
	fluid->viscosityCoe = viscosityCoeView.getValue();
	fluid->heatDiffuseCoe = heatDiffuseCoeView.getValue();
	fluid->dragForceCoe = dragForceCoeView.getValue();
	fluid->dragHeatCoe = dragHeatCoeView.getValue();

	//this->fluid->reset(getWorld());
}