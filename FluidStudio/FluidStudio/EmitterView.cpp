#include "EmitterView.h"
#include "EmitterModel.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

EmitterView::EmitterView(const std::string& name, World* world, Canvas* canvas) :
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

void EmitterView::setValue(EmitterModel* emitter)
{
	this->emitter = emitter;
	this->pressureCoeView.setValue(emitter->pressureCoe);
	this->viscosityCoeView.setValue(emitter->viscosityCoe);
	this->heatDiffuseCoeView.setValue(emitter->heatDiffuseCoe);
	this->dragForceCoeView.setValue(emitter->dragForceCoe);
	this->dragHeatCoeView.setValue(emitter->dragHeatCoe);
}

void EmitterView::onOk()
{
	emitter->pressureCoe = pressureCoeView.getValue();
	emitter->viscosityCoe = viscosityCoeView.getValue();
	emitter->heatDiffuseCoe = heatDiffuseCoeView.getValue();
	emitter->dragForceCoe = dragForceCoeView.getValue();
	emitter->dragHeatCoe = dragHeatCoeView.getValue();
}