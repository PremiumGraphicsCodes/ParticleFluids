#include "MainModel.h"

using namespace Crystal::UI;

void MainModel::createFluidScene()
{
	this->fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");
	world->getScenes()->addScene(fluidScene);
}

void MainModel::createStaticScene()
{
	this->staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");
	world->getScenes()->addScene(staticScene);
}

void MainModel::createEmitterScene()
{
	this->emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	world->getScenes()->addScene(emitterScene);
}
