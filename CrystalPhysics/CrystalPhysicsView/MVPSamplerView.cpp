#include "MVPSamplerView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MVPSamplerView::MVPSamplerView(const std::string& name, World* model, Canvas* canvas) :
	IView(name),
	world(model),
	canvas(canvas),
	splitButton("Split"),
	mergeButton("Merge")
{
	splitButton.setFunction([=]() { onSplit(); });
	add(&splitButton);

	mergeButton.setFunction([=]() { onMerge(); });
	add(&mergeButton);

	/*
	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&vorticityCoeView);
	add(&timeStepView);
	add(&radiusView);

	fluidScene = new MVPFluidScene(world->getNextSceneId(), "KFFluid");
	world->getScenes()->addScene(fluidScene);

	staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");
	world->getScenes()->addScene(staticScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");


	world->addAnimation(&solver);
	world->addAnimation(&updator);
	*/
}

void MVPSamplerView::onSplit()
{

}

void MVPSamplerView::onMerge()
{

}
