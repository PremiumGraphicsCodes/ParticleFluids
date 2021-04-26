#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFFluidScene::KFFluidScene(const int id, const std::string& name) :
	IKFFluidScene(id, name),
	isBoundary_(false)
{
}
