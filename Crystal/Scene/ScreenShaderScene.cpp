#include "ScreenShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenShaderScene::ScreenShaderScene()
{
}

void ScreenShaderScene::add(IShaderScene* scene)
{
	this->scenes.push_back(scene);
}