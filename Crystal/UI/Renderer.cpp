#include "Renderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"
#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Scene/TextureScene.h"

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

bool Renderer::build(ShaderObjectRepository& shaders, IScene* scene, SceneFactory* factory)
{
	if (!objectRenderer.build(shaders)) {
		return false;
	}
	if (!objectIdRenderer.build(shaders, scene, factory)) {
		return false;
	}

	if (!renderer.build(shaders)) {
		return false;
	}
	return true;
}

void Renderer::render(const int width, const int height, IScene* scene)
{
	//const auto& tex = scene->findSceneByName<TextureScene*>("MainTexture");
	const auto& smoothTex = scene->findSceneByName<TextureScene*>("SmoothTexture");
	const auto& onScreenTex = scene->findSceneByName<TextureScene*>("OnScreenTexture");
	objectRenderer.render(*onScreenTex->getTexture(), *smoothTex->getTexture());
	objectIdRenderer.render();


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