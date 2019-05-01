#include "ObjectRenderer.h"
#include "../../Crystal/UI/ObjectViewModel.h"
#include "../../Crystal/UI/AppearanceViewModel.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

bool ObjectRenderer::build(ShaderObjectRepository& shaders)
{
	if (!pointRenderer.build(shaders)) {
		return false;
	}
	if (!wireRenderer.build(shaders)) {
		return false;
	}
	if (!smoothRenderer.build()) {
		return false;
	}

	frameBufferObject.build(512, 512);
	return true;
}

void ObjectRenderer::setViewModel(const ObjectViewModel& vm, const AppearanceViewModel& avm)
{
	this->pointRenderer.setBuffer(vm.getPointBuffer());
	this->wireRenderer.setBuffer(vm.getLineBuffer(), 1.0f);
	smoothBuffers.clear();
	for (const auto& tb : vm.getTriangleBuffers()) {
		Shader::SmoothRenderer::Buffer buffer;
		buffer.triangle = tb;
		buffer.light = avm.getLightBuffer();
		buffer.material = avm.getMaterialBuffer();
		smoothBuffers.push_back(buffer);
	}
}

void ObjectRenderer::render(const TextureObject& texture, const TextureObject& smoothTexture)
{
	frameBufferObject.setTexture(texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointRenderer.render(*camera);
	wireRenderer.render(*camera);
	for (const auto& b : smoothBuffers) {
		smoothRenderer.render(b, *camera, smoothTexture);
	}
	//texture.unbind();
	frameBufferObject.unbind();
}