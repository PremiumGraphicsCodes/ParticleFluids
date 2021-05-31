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

ShaderBuildStatus ScreenShader::build(GLObjectFactory& factory)
{
	const auto prStatus = pointRenderer->build(factory);
	if(!prStatus.isOk) {
		return prStatus;
	}
	const auto wrStatus = wireRenderer->build(factory);
	if(!wrStatus.isOk){
		return wrStatus;
	}
	if (!triagleRenderer->build(factory)) {
		ShaderBuildStatus status;
		status.isOk = false;
		return status;
	}

	/*
	if (!smoothRenderer->build(factory).isOk) {
		return false;
	}
	*/

	texture = factory.createTextureObject();
	texture->send(Image(512, 512));
	frameBufferObject = factory.createFrameBufferObject();
	frameBufferObject->build(512, 512);
	ShaderBuildStatus status;
	status.isOk = true;
	return status;
}

void ScreenShader::release(GLObjectFactory& factory)
{
	pointRenderer->release(factory);
	wireRenderer->release(factory);
	//smoothRenderer->release(factory);
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
