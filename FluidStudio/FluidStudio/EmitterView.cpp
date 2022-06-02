#include "EmitterView.h"
#include "EmitterModel.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

using namespace PG::FS;

EmitterView::EmitterView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	idView("Id", -1),
	psIdView("ParticleSystemId", -1),
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	heatDiffuseCoeView("HeatDiffuseCoe", 100.0f),
	dragHeatCoeView("DragHeatCoe", 0.0),
	dragForceCoeView("DragForceCoe", 0.0),
	temperatureView("Temperature", 300.0f),
	lifeLimitView("LifeLimit", 500),
	velocityView("Velocity", Vector3df(0,0,0))
{
	add(&idView);
	add(&psIdView);
	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&heatDiffuseCoeView);
	add(&dragHeatCoeView);
	add(&dragForceCoeView);
	add(&temperatureView);
	add(&lifeLimitView);
	add(&velocityView);
}

void EmitterView::setValue(EmitterModel* emitter)
{
	this->emitter = emitter;
	this->idView.setValue(emitter->fluidId);
	this->psIdView.setValue(emitter->particleSystemId);
	this->pressureCoeView.setValue(emitter->pressureCoe);
	this->viscosityCoeView.setValue(emitter->viscosityCoe);
	this->heatDiffuseCoeView.setValue(emitter->heatDiffuseCoe);
	this->dragForceCoeView.setValue(emitter->dragForceCoe);
	this->dragHeatCoeView.setValue(emitter->dragHeatCoe);
	this->temperatureView.setValue(emitter->temperature);
	this->lifeLimitView.setValue(emitter->lifeLimit);
	this->velocityView.setValue(emitter->initialVelocity);
}

void EmitterView::onOk()
{
	emitter->particleSystemId = psIdView.getValue();
	emitter->pressureCoe = pressureCoeView.getValue();
	emitter->viscosityCoe = viscosityCoeView.getValue();
	emitter->heatDiffuseCoe = heatDiffuseCoeView.getValue();
	emitter->dragForceCoe = dragForceCoeView.getValue();
	emitter->dragHeatCoe = dragHeatCoeView.getValue();
	emitter->temperature = temperatureView.getValue();
	emitter->lifeLimit = lifeLimitView.getValue();
	emitter->initialVelocity = velocityView.getValue();
}