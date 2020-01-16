#include "SceneIdRenderer.h"
#include "../../Crystal/Scene/Scene.h"
#include "../../Crystal/Scene/SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

bool SceneIdRenderer::build()
{
	if (!pointIdRenderer.build()) {
		return false;
	}
	if (!lineIdRenderer.build()) {
		return false;
	}
	if (!triangleIdRenderer.build()) {
		return false;
	}

	frameBufferObject.build(512, 512);

	texture.create(Imagef(512, 512), 0);

	return true;
}

void SceneIdRenderer::render(Camera* camera, const SceneIdViewModel& vm)
{
	const auto& pointBuffers = vm.pointIdBuffers;
	const auto& lineBuffers = vm.lineIdBuffers;
	const auto& triangleBuffers = vm.triangleIdBuffers;

	frameBufferObject.setTexture(texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (const auto& b : pointBuffers) {
		pointIdRenderer.setBuffer(b);
		pointIdRenderer.render(*camera);
	}
	for (const auto& b : lineBuffers) {
		lineIdRenderer.setBuffer(b);
		lineIdRenderer.render(*camera);
	}
	for (const auto& b : triangleBuffers) {
		triangleIdRenderer.setBuffer(b);
		triangleIdRenderer.render(*camera);
	}

	frameBufferObject.unbind();
}

DrawableID SceneIdRenderer::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture.getWidth(), y * texture.getHeight());
}

DrawableID SceneIdRenderer::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	const auto& color = frameBufferObject.getColor(x, y);
	frameBufferObject.unbind();
	return DrawableID(color);
}