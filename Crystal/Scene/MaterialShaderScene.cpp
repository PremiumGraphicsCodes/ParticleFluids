#include "MaterialShaderScene.h"

#include "IMaterialScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void MaterialShaderScene::update(const int index) {
	for (auto s : parentScenes) {
		s->sendMaterial(index, materials[index]);
	}
}