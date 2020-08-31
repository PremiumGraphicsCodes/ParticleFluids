#include "ScreenShader.h"

#include "../Shader/GLObjectFactory.h"

#include "ScreenShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TextureScene.h"
#include "LightScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenShader::ScreenShader(const std::string& name) :
	IShaderScene(name),
	pointRenderer(new PointRenderer()),
	wireRenderer(new LineRenderer()),
	smoothRenderer(new SmoothShader("SmoothRenderer")),
	triagleRenderer(new TriangleRenderer()),
	buffer("ScreenBuffer")
{
	texture = new TextureShaderScene("ScreenTex");// = factory.getTextureFactory()->createTextureObject("Scene",Image(512, 512));
}

bool ScreenShader::build(GLObjectFactory& factory)
{
	if (!pointRenderer->build(factory)) {
		return false;
	}
	if (!wireRenderer->build(factory)) {
		return false;
	}
	if (!smoothRenderer->build(factory)) {
		return false;
	}
	if (!triagleRenderer->build(factory)) {
		return false;
	}

	texture->build(factory);
	texture->send(Image(512, 512));
	//texture.create(, 1);
	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);
	return true;
}

void ScreenShader::release(GLObjectFactory& factory)
{
	//TODO;
}

void ScreenShader::setBuffer(const ScreenShaderScene& buffer)
{
	this->buffer = buffer;
}

void ScreenShader::render()
{
	auto texture = *this->texture->getTextureObject();
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		const auto& pointBuffers = buffer.getPointBuffers();
		for (auto pb : pointBuffers) {
			pb->render();
		}
	}

	if (mask.showLines) {
		const auto& lineBuffers = buffer.getLineBuffers();
		for (auto lb : lineBuffers) {
			lb->render();
		}
	}
	if (mask.showTrianlges) {
		const auto& pmScenes = buffer.getSmoothBuffers();
		for (auto pm : pmScenes) {
			pm->render();
//			smoothRenderer->send(*pm);
//			smoothRenderer->render();
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}