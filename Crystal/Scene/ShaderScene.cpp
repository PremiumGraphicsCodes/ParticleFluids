#include "ShaderScene.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool ShaderScene::build()
{
	this->shader = std::make_unique<ShaderObject>();
	if (!shader->build(vsSource, fsSource)) {
		return false;
	}
	for (const auto& u : uniforms) {
		shader->findUniformLocation(u);
	}
	for (const auto& a : attributes) {
		shader->findAttribLocation(a);
	}
	return true;
}