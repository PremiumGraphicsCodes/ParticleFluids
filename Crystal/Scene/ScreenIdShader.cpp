#include "ScreenIdShader.h"
#include "../../Crystal/Scene/SceneIdShaderBuffer.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool ScreenIdShader::build(GLObjectFactory& factory)
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

void ScreenIdShader::render(Camera* camera, const ScreenIdShaderBuffer& vm)
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
		pointBuffer.camera = *camera;
		pointBuffer.send(b);
		pointIdRenderer.send(pointBuffer);
		pointIdRenderer.render();
	}
	for (const auto& b : lineBuffers) {
		lineBuffer.send(b);
		lineIdRenderer.setBuffer(lineBuffer);
		lineIdRenderer.render();
	}
	for (const auto& b : triangleBuffers) {
		triangleBuffer.send(b);
		triangleIdRenderer.setBuffer(triangleBuffer);
		triangleIdRenderer.render(*camera);
	}

	frameBufferObject->unbind();
}

DrawableID ScreenIdShader::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture.getWidth(), y * texture.getHeight());
}

DrawableID ScreenIdShader::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	const auto& color = frameBufferObject->getColor(x, y);
	frameBufferObject->unbind();
	return DrawableID(color);
}