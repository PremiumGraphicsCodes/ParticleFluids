#include "FluidScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Algo::Physics;

FluidScene::FluidScene(const int id, const std::string& name) :
	IScene(id, name)
{
	this->controller = std::make_unique<FluidSceneController>(this);
}
