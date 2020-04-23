#include "ScreenIdShader.h"
#include "../../Crystal/Scene/ScreenIdShaderScene.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenIdShader::ScreenIdShader(const std::string& name) :
	IShaderScene(name),
	pointBuffer("PointIdBuffer"),
	lineBuffer("LineIdBuffer"),
	pointIdRenderer("PointIdRenderer"),
	lineIdRenderer("LineIdRenderer"),
	texture("IdTexture")
{
	addChild(&texture);
}

bool ScreenIdShader::build(GLObjectFactory& factory)
{
	if (!pointIdRenderer.build(factory)) {
		return false;
	}
	if (!lineIdRenderer.build(factory)) {
		return false;
	}
	if (!triangleIdRenderer.build()) {
		return false;
	}

	pointBuffer.build(factory);
	lineBuffer.build(factory);
	triangleBuffer.build();

	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);

	texture.build(factory);
	texture.send(Image(512, 512));
	//texture = factory.getTextureFactory()->createTextureObject("SceneId", Imagef(512, 512));

	return true;
}

void ScreenIdShader::release(GLObjectFactory& factory)
{

}

void ScreenIdShader::render(Camera* camera, const ScreenIdShaderScene& vm)
{
	const auto& pointBuffers = vm.pointIdBuffers;
	const auto& lineBuffers = vm.lineIdBuffers;
	const auto& triangleBuffers = vm.triangleIdBuffers;

	frameBufferObject->setTexture(*texture.getTextureObject());
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getTextureObject()->getWidth(), texture.getTextureObject()->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
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
	*/

	frameBufferObject->unbind();
}

void ScreenIdShader::render()
{

}

DrawableID ScreenIdShader::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture.getTextureObject()->getWidth(), y * texture.getTextureObject()->getHeight());
}

DrawableID ScreenIdShader::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject->bind();
	glViewport(0, 0, texture.getTextureObject()->getWidth(), texture.getTextureObject()->getHeight());
	const auto& color = frameBufferObject->getColor(x, y);
	frameBufferObject->unbind();
	return DrawableID(color);
}