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

SolverView::SolverView(const std::string& name, World* world, Canvas* canvas, MainModel* mainModel) :
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

	mainModel->csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");

	model->exporter = new SolverExporter(world);

	boundaryView.setValue(Box3dd(Vector3dd(-20, 0, -20), Vector3dd(20, 20, 20)));

	world->addAnimation(&model->solver);
	world->addAnimation(&model->updator);
	world->addAnimation(model->exporter);
}

void SolverView::onStart()
{
	onReset();
}

void SolverView::onReset()
{
	model->resetSolver();
	//model->solver.clear();

	model->solver.setExternalForce(this->externalForceView.getValue());
	model->solver.setBuoyancy(this->buoyancyView.getValue());


	//this->addEmitter();

	//model->solver.clear();
	model->csgScene->add(boundaryView.getValue());
	model->solver.addBoundary(model->csgScene);
	model->solver.setEffectLength(radiusView.getValue());

	model->solver.setMaxTimeStep(this->timeStepView.getValue());
	model->solver.setupBoundaries();


	model->csgScene->clearBoxes();
	model->csgScene->add(boundaryView.getValue());

	model->exporter->reset();
	model->exporter->setSolver(&model->solver);
	model->exporter->setDirectory(this->exportDirecotryView.getPath());
	model->exporter->setActive(doExportView.getValue());
	model->exporter->setExportInterval(this->exportIntervalView.getValue());
	//this->addEmitter();
}
