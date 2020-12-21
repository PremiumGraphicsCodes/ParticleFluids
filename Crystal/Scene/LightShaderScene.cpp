#include "LightShaderScene.h"
#include "ILightScene.h"

using namespace Crystal::Scene;

void LightShaderScene::update(const int index)
{
	for (auto s : parentScenes) {
		s->sendLight(index, lights[index]);
	}
}
