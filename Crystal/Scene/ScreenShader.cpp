#include "ScreenShader.h"

#include "../Shader/GLObjectFactory.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TextureScene.h"
#include "LightScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenShader::ScreenShader(const std::string& name) :
	pointRenderer(new PointRenderer()),
	wireRenderer(new LineRenderer()),
	smoothRenderer(new SmoothRenderer()),
	triagleRenderer(new TriangleRenderer()),
	texture(nullptr),
	frameBufferObject(nullptr)
{
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

	texture = factory.createTextureObject();
	texture->send(Image(512, 512));
	frameBufferObject = factory.createFrameBufferObject();
	frameBufferObject->build(512, 512);
	return true;
}

void ScreenShader::release(GLObjectFactory& factory)
{
	pointRenderer->release(factory);
	wireRenderer->release(factory);
	smoothRenderer->release(factory);
	triagleRenderer->release(factory);

	factory.remove(texture);
	factory.remove(frameBufferObject);
}

void ScreenShader::render(const Camera& camera)
{
	frameBufferObject->setTexture(*texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture->getWidth(), texture->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto s : scenes) {
		s->render(camera);
	}

	frameBufferObject->unbind();
}
