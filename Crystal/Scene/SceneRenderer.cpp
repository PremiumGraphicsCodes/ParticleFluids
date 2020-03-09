#include "SceneRenderer.h"
#include "../../Crystal/Scene/SceneViewModel.h"

#include "../Shader/GLObjectFactory.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

bool SceneRenderer::build(GLObjectFactory& factory)
{
	if (!pointRenderer.build(factory)) {
		return false;
	}
	if (!wireRenderer.build(factory)) {
		return false;
	}
	if (!smoothRenderer.build(factory)) {
		return false;
	}

	texture = factory.getTextureFactory()->createTextureObject("Scene",Image(512, 512));
	//texture.create(, 1);
	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);
	return true;
}

void SceneRenderer::render(Camera* camera, const SceneViewModel& vm)
{
//	const auto& pointBuffers = vm.getPointBuffers();
//	const auto& lineBuffers = vm.getLineBuffers();
	const auto& smoothBuffers = vm.getTriangleBuffers();
	const auto& materials = vm.getMaterials();
	const auto& lights = vm.getLights();

	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (auto s : particleScenes) {
			pointRenderer.setBuffer(s->getGLBuffer());
			pointRenderer.render(*camera);

		}
	}
	if (mask.showLines) {
		for (auto s : wfScenes) {
			wireRenderer.setBuffer(s->getGLBuffer());
			wireRenderer.render(*camera);
		}
	}
	if (mask.showTrianlges) {
		smoothRenderer.setMaterials(materials);
		smoothRenderer.setLights(lights);
		smoothRenderer.setTextures(vm.getTextures());
		for (const auto& b : smoothBuffers) {
			smoothRenderer.setBuffer(b);
			smoothRenderer.render(*camera);
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}