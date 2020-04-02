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

bool ScreenShader::build(GLObjectFactory& factory)
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

void ScreenShader::release(GLObjectFactory& factory)
{
	//TODO;
}

void ScreenShader::setBuffer(Camera* camera, const ScreenShaderScene& buffer)
{
	this->camera = camera;
	this->buffer = buffer;
}

void ScreenShader::render()
{
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const auto& children = buffer.getChildren();
	for (auto buffer : children) {
		buffer->render();
	}

	if (mask.showLines) {
		for (auto lb : buffer.lineBuffers) {
			lb.camera = *camera;
			wireRenderer.setBuffer(lb);
			wireRenderer.render();
		}
	}
	if (mask.showTrianlges) {
		std::vector<Material> mBuffer;
		for (auto m : buffer.materialScenes) {
			mBuffer.push_back(*m->getMaterial());
		}
		smoothRenderer.send(mBuffer);
		std::vector<PointLight> lBuffer;
		for (auto l : buffer.lightScenes) {
			lBuffer.push_back(*l->getLight());
		}
		for (auto pm : buffer.pmScenes) {
			pm.camera = *camera;
			smoothRenderer.send(pm);
			smoothRenderer.render();
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}