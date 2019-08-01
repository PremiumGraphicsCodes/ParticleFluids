#include "ShaderScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneViewModel ShaderScene::toViewModel() const
{
	return SceneViewModel();
}

SceneIdViewModel ShaderScene::toIdViewModel() const
{
	return SceneIdViewModel();
}

bool ShaderScene::onBuild()
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