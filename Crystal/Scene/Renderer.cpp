#include "Renderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"
#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Scene/TextureScene.h"
#include "../../Crystal/Scene/ShaderScene.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Renderer::Renderer(Crystal::Graphics::ICamera* camera) :
	objectRenderer(camera),
	objectIdRenderer(camera),
	showOffScreen(false),
	smoothTex(-1, "", Image(512,512)),
	onScreenTex(-1, "", Image(512, 512)),
	idTex(-1, "", Image(512, 521))
{
}

bool Renderer::build(IShaderScene* sscene)
{
	if (!objectRenderer.build()) {
		return false;
	}
	if (!objectIdRenderer.build()) {
		return false;
	}

	if (!renderer.build()) {
		return false;
	}

	if (!sscene->build()) {
		return false;
	}

	smoothTex.build();
	onScreenTex.build();
	idTex.build();

	return true;
}

void Renderer::render(const int width, const int height, IShaderScene* scene, const ViewModel& vm)
{
	//const auto& tex = scene->findSceneByName<TextureScene*>("MainTexture");
	objectRenderer.render(vm.object, *onScreenTex.getTexture(), *smoothTex.getTexture());
	objectIdRenderer.render(vm.objectId, *idTex.getTexture());

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
	renderer.render(*onScreenTex.getTexture());
}