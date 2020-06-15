#include "PBFluidScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;

PBFluidScene::PBFluidScene(const int id, const std::string& name) :
	IScene(id, name)
{
	//this->controller = std::make_unique<FluidSceneController>(this);
}
