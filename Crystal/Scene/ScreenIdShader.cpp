#include "ScreenIdShader.h"
#include "../../Crystal/Scene/ScreenIdShaderScene.h"

#include "../Shader/GLObjectFactory.h"

#include "PointShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenIdShader::ScreenIdShader(const std::string& name) :
	IShaderScene(name),
	lineBuffer("LineIdBuffer"),
	//lineIdRenderer("LineIdRenderer"),
	triangleBuffer("TriangleIdBuffer"),
	buffer("ScreenIdBuffer")
{
	texture = new TextureShaderScene("IdTexture");
}

bool ScreenIdShader::build(GLObjectFactory& factory)
{
	lineBuffer.build(factory);
	triangleBuffer.build(factory);

	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);

	texture->build(factory);
	texture->send(Image(512, 512));
	//texture = factory.getTextureFactory()->createTextureObject("SceneId", Imagef(512, 512));

	return true;
}

void ScreenIdShader::release(GLObjectFactory& factory)
{

}

void ScreenIdShader::setBuffer(const ScreenIdShaderScene& vm)
{
	this->buffer = vm;
}

void ScreenIdShader::render()
{
	//const auto& pointBuffers = vm.pointIdBuffers;
	//const auto& lineBuffers = vm.lineIdBuffers;
	//const auto& triangleBuffers = vm.triangleIdBuffers;

	frameBufferObject->setTexture(*texture->getTextureObject());
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture->getTextureObject()->getWidth(), texture->getTextureObject()->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	const auto& pbs = buffer.getPointScenes();
	for (auto pb : pbs) {
		pb->render();
	}
	const auto& lbs = buffer.getLineScenes();
	for (auto lb : lbs) {
		lb->render();
	}
	const auto& tbs = buffer.getTriangleScenes();
	for (auto tb : tbs) {
		tb->render();
	}

	frameBufferObject->unbind();
}

DrawableID ScreenIdShader::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture->getTextureObject()->getWidth(), y * texture->getTextureObject()->getHeight());
}

DrawableID ScreenIdShader::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject->bind();
	glViewport(0, 0, texture->getTextureObject()->getWidth(), texture->getTextureObject()->getHeight());
	const auto& color = frameBufferObject->getColor(x, y);
	frameBufferObject->unbind();
	return DrawableID(color);
}