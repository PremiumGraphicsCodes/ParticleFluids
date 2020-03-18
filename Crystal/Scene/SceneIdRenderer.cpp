#include "SceneIdRenderer.h"
#include "../../Crystal/Scene/Scene.h"
#include "../../Crystal/Scene/SceneIdViewModel.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool SceneIdRenderer::build(GLObjectFactory& factory)
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

	pointBuffer.build();
	lineBuffer.build();
	triangleBuffer.build();

	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);

	texture = factory.getTextureFactory()->createTextureObject("SceneId", Imagef(512, 512));

	return true;
}

void SceneIdRenderer::render(Camera* camera, const SceneIdViewModel& vm)
{
	const auto& pointBuffers = vm.pointIdBuffers;
	const auto& lineBuffers = vm.lineIdBuffers;
	const auto& triangleBuffers = vm.triangleIdBuffers;

	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (const auto& b : pointBuffers) {
		pointBuffer.send(b);
		pointIdRenderer.send(pointBuffer, *camera);
		pointIdRenderer.render();
	}
	for (const auto& b : lineBuffers) {
		lineBuffer.send(b);
		lineIdRenderer.setBuffer(lineBuffer);
		lineIdRenderer.render(*camera);
	}
	for (const auto& b : triangleBuffers) {
		triangleBuffer.send(b);
		triangleIdRenderer.setBuffer(triangleBuffer);
		triangleIdRenderer.render(*camera);
	}

	frameBufferObject->unbind();
}

DrawableID SceneIdRenderer::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture.getWidth(), y * texture.getHeight());
}

DrawableID SceneIdRenderer::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	const auto& color = frameBufferObject->getColor(x, y);
	frameBufferObject->unbind();
	return DrawableID(color);
}