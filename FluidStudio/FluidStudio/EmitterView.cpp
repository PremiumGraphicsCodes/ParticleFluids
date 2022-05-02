#include "EmitterView.h"

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

void EmitterView::setValue(MVPFluidEmitterScene* emitter)
{
	this->emitterScene = emitter;
	this->pressureCoeView.setValue(emitter->getPressure());
	this->viscosityCoeView.setValue(emitter->getViscosityCoe());
	this->heatDiffuseCoeView.setValue(emitter->getHeatDiffuseCoe());
	this->dragForceCoeView.setValue(emitter->getDragForceCoe());
	this->dragHeatCoeView.setValue(emitter->getDragHeatCoe());
}

void EmitterView::onOk()
{
	emitterScene->setPressureCoe(pressureCoeView.getValue());
	emitterScene->setViscosityCoe(viscosityCoeView.getValue());
	emitterScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	emitterScene->setDragForceCoe(dragForceCoeView.getValue());
	emitterScene->setDragHeatCoe(dragHeatCoeView.getValue());
}