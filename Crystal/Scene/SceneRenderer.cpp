#include "SceneRenderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

bool SceneRenderer::build()
{
	if (!pointRenderer.build()) {
		return false;
	}
	if (!wireRenderer.build()) {
		return false;
	}
	if (!smoothRenderer.build()) {
		return false;
	}

	frameBufferObject.build(512, 512);
	return true;
}

void SceneRenderer::render(const SceneViewModel& vm, const TextureObject& texture)
{
	const auto& pointBuffers = vm.getPointBuffers();
	const auto& lineBuffers = vm.getLineBuffers();
	const auto& smoothBuffers = vm.getTriangleBuffers();
	const auto& lights = vm.getLights();

	frameBufferObject.setTexture(texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (const auto& b : pointBuffers) {
		pointRenderer.setBuffer(b);
		pointRenderer.render(*camera);
	}
	for (const auto& b : lineBuffers) {
		wireRenderer.setBuffer(b, 1.0f);
		wireRenderer.render(*camera);
	}
	smoothRenderer.setLights(lights);
	for (const auto& b : smoothBuffers) {
		smoothRenderer.setBuffer(b);
		smoothRenderer.render(*camera);
	}
	//texture.unbind();
	frameBufferObject.unbind();
}