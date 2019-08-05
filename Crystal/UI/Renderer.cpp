#include "Renderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"
#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Scene/TextureScene.h"
#include "../../Crystal/Scene/ShaderScene.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Renderer::Renderer(Crystal::Graphics::ICamera* camera) :
	objectRenderer(camera),
	objectIdRenderer(camera),
	showOffScreen(false)
{
}

bool Renderer::build(IScene* scene, SceneFactory* factory, IShaderScene* sscene)
{
	if (!objectRenderer.build()) {
		return false;
	}
	if (!objectIdRenderer.build(scene, factory)) {
		return false;
	}

	if (!renderer.build()) {
		return false;
	}

	if (!sscene->build()) {
		return false;
	}
	return true;
}

void Renderer::render(const int width, const int height, IShaderScene* scene)
{
	//const auto& tex = scene->findSceneByName<TextureScene*>("MainTexture");
	const auto& smoothTex = scene->findSceneByName<TextureScene*>("SmoothTexture");
	const auto& onScreenTex = scene->findSceneByName<TextureScene*>("OnScreenTexture");
	const auto& idTex = scene->findSceneByName<TextureScene*>("IdTexture");
	objectRenderer.render(*onScreenTex->getTexture(), *smoothTex->getTexture());
	objectIdRenderer.render(*idTex->getTexture());


	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	if (showOffScreen) {
		renderer.render(*objectIdRenderer.getTexture());// *tex);
	}
	else {
		renderer.render(*tex);
	}
	*/
	renderer.render(*onScreenTex->getTexture());
}