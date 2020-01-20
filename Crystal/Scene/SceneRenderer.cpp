#include "SceneRenderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"

#include "../Shader/GLObjectFactory.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

bool SceneRenderer::build(GLObjectFactory& factory)
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

	texture = factory.getTextureFactory()->createTextureObject(Image(512, 512));
	//texture.create(, 1);
	frameBufferObject.build(512, 512);
	return true;
}

void SceneRenderer::render(Camera* camera, const SceneViewModel& vm)
{
	const auto& pointBuffers = vm.getPointBuffers();
	const auto& lineBuffers = vm.getLineBuffers();
	const auto& smoothBuffers = vm.getTriangleBuffers();
	const auto& materials = vm.getMaterials();
	const auto& lights = vm.getLights();

	frameBufferObject.setTexture(*texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture->getWidth(), texture->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (const auto& b : pointBuffers) {
			pointRenderer.setBuffer(b);
			pointRenderer.render(*camera);
		}
	}
	if (mask.showLines) {
		for (const auto& b : lineBuffers) {
			wireRenderer.setBuffer(b);
			wireRenderer.render(*camera);
		}
	}
	if (mask.showTrianlges) {
		smoothRenderer.setMaterials(materials);
		smoothRenderer.setLights(lights);
		for (const auto& b : smoothBuffers) {
			smoothRenderer.setBuffer(b, vm.getTextures());
			smoothRenderer.render(*camera);
		}
	}
	//texture.unbind();
	frameBufferObject.unbind();
}