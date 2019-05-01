#include "Renderer.h"
#include "../../Crystal/UI/ObjectViewModel.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Shader;
using namespace Crystal::Model;
using namespace Crystal::UI;

Renderer::Renderer(Crystal::Graphics::ICamera* camera) :
	objectRenderer(camera),
	objectIdRenderer(camera),
	showOffScreen(false)
{
}

bool Renderer::build(ShaderObjectRepository& shaders, TextureObjectRepository& textures)
{
	if (!objectRenderer.build(shaders)) {
		return false;
	}
	if (!objectIdRenderer.build(shaders, textures)) {
		return false;
	}

	if (!renderer.build(shaders)) {
		return false;
	}
	return true;
}

void Renderer::render(const int width, const int height, const TextureObjectRepository& textures)
{
	const auto& texx = textures.getTextures();
	const auto& tex = texx[0];
	const auto& smoothTex = texx[1];
	objectRenderer.render(*tex, *smoothTex);
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
	renderer.render(*textures.getOnScreenTexture());
}