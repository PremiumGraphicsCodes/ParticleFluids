#include "SceneShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

void SceneShaderScene::add(ParticleSystemScene* scene, GLObjectFactory& glFactory) {
	screen.add(scene, glFactory);
}
