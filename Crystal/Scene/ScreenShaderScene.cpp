#include "ScreenShaderScene.h"

#include "../Shader/GLObjectFactory.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TextureScene.h"
#include "LightScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool ScreenShaderScene::build(GLObjectFactory& factory)
{
	if (!pointRenderer.build()) {
		return false;
	}
	if (!wireRenderer.build()) {
		return false;
	}
	if (!smoothRenderer.build()) {
		return false;
	}

	texture = factory.getTextureFactory()->createTextureObject("Scene",Image(512, 512));
	//texture.create(, 1);
	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);
	return true;
}

void ScreenShaderScene::add(ParticleSystemScene* scene)
{
	const auto& ps = scene->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}

	PointShaderBuffer buffer;
	buffer.build();
	buffer.send(pb);
	pointBuffers.push_back(buffer);
}

void ScreenShaderScene::render(Camera* camera)
{
	this->camera = camera;
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (auto s : pointBuffers) {
			pointRenderer.send(s, *camera);
			pointRenderer.render();
		}
	}
	if (mask.showLines) {
		for (auto s : wfScenes) {
			auto bf = s->getGLBuffer();
			bf.camera = *camera;
			wireRenderer.setBuffer(bf);
			wireRenderer.render();
		}
	}
	if (mask.showTrianlges) {
		MaterialShaderBuffer mBuffer;
		for (auto m : materialScenes) {
			mBuffer.add(*m->getMaterial());
		}
		LightShaderBuffer lBuffer;
		for (auto l : lightScenes) {
			lBuffer.add(*l->getLight());
		}
		TextureShaderBuffer texBuffer;
		for (auto tex : textureScenes) {
			texBuffer.add(tex->getTextureObject());
		}
		for (auto pm : pmScenes) {
	//		smoothRenderer.send();
			smoothRenderer.render();
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}