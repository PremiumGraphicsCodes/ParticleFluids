#include "SolverView.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "CrystalPhysics/CrystalPhysics/Boundary/CSGBoundaryScene.h"
#include "SolverExporter.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalScene/Scene/IAnimator.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsSolverExportCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

SolverView::SolverView(const std::string& name, World* world, Canvas* canvas, SolverModel* mainModel) :
	IView(name),
	model(mainModel),
	world(world),
	canvas(canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary"),
	timeStepView("TimeStep", 0.01f),
	radiusView("SearchRadius", 2.00f),
	externalForceView("ExternalForce", Vector3dd(0.0, -9.8, 0.0)),
	buoyancyView("Buoyancy", Vector3df(0.0, 0.098, 0.0)),
	doExportView("Export", false),
	exportIntervalView("Interval", 5),
	exportDirecotryView("ExportDir", "./")
{
	startButton.setFunction([=]() { onStart(); });
	add(&startButton);

	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);

	add(&boundaryView);
	add(&timeStepView);
	add(&radiusView);
	add(&externalForceView);
	add(&buoyancyView);
	add(&doExportView);
	add(&exportIntervalView);
	add(&exportDirecotryView);


	boundaryView.setValue(Box3dd(Vector3dd(-20, 0, -20), Vector3dd(20, 20, 20)));
}

void SolverView::onStart()
{
	onReset();
}

void SolverView::onReset()
{
	model->reset(world);
	//model->solver.clear();

	model->getSolver()->setExternalForce(this->externalForceView.getValue());
	model->getSolver()->setBuoyancy(this->buoyancyView.getValue());

	model->getSolver()->setEffectLength(radiusView.getValue());

	model->getSolver()->setMaxTimeStep(this->timeStepView.getValue());
	model->getSolver()->setupBoundaries();


	model->getBoundary()->clearBoxes();
	model->getBoundary()->add(boundaryView.getValue());
	model->getSolver()->addBoundary(model->getBoundary());

	model->getExporter()->reset();
	model->getExporter()->setSolver(model->getSolver());
	model->getExporter()->setDirectory(this->exportDirecotryView.getPath());
	model->getExporter()->setActive(doExportView.getValue());
	model->getExporter()->setExportInterval(this->exportIntervalView.getValue());
	//this->addEmitter();
}
