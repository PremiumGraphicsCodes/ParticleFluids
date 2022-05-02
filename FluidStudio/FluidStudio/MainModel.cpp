#include "MainModel.h"

using namespace Crystal::UI;

void MainModel::createEmitterScene()
{
	this->emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	world->getScenes()->addScene(emitterScene);
}
