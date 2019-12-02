#include "Renderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"
#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Scene/IRenderer.h"

#include "../Graphics/PerspectiveCamera.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Renderer::Renderer() :
	showOffScreen(false),
	camera(new PerspectiveCamera(
		1.0,
		0.5f * PI,
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		1.0f, 10.0f))
{

}

bool Renderer::build()
{
	if (!objectRenderer.build()) {
		return false;
	}
	if (!parentIdRenderer.build()) {
		return false;
	}
	if (!childIdRenderer.build()) {
		return false;
	}

	if (!renderer.build()) {
		return false;
	}

	return true;
}

void Renderer::render(const int width, const int height, const ViewModel& vm)
{
	objectRenderer.render(camera.get(), vm.object);
	parentIdRenderer.render(camera.get(), vm.parentId);
	childIdRenderer.render(camera.get(), vm.childId);

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