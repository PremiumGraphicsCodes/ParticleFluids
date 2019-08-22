#include "Renderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"
#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Scene/IRenderer.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Renderer::Renderer(Crystal::Graphics::ICamera* camera) :
	objectRenderer(camera),
	objectIdRenderer(camera),
	showOffScreen(false)
{
}

bool Renderer::build()
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

	return true;
}

void Renderer::render(const int width, const int height, const ViewModel& vm)
{
	objectRenderer.render(vm.object);
	objectIdRenderer.render(vm.objectId);

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
	auto texture = objectRenderer.getTexture();
	renderer.render(*texture);
}