#include "SceneRenderer.h"

#include "../Shader/GLObjectFactory.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TextureScene.h"
#include "LightScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool SceneRenderer::build(GLObjectFactory& factory)
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

void SceneRenderer::render(Camera* camera)
{
	this->camera = camera;
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (auto s : particleScenes) {
			s->render(this);
		}
	}
	if (mask.showLines) {
		for (auto s : wfScenes) {
			s->render(this);
		}
	}
	if (mask.showTrianlges) {
		MaterialRenderer::GLBuffer mBuffer;
		for (auto m : materialScenes) {
			mBuffer.add(*m->getMaterial());
		}
		LightRenderer lBuffer;
		for (auto l : lightScenes) {
			lBuffer.add(*l->getLight());
		}
		std::vector<TextureObject> textures;
		for (auto tex : textureScenes) {
			textures.push_back(tex->getTextureObject());
		}
		smoothRenderer.getTextureRenderer()->setTextures(textures, smoothRenderer.getShader());
		for (auto pm : pmScenes) {
			pm->render(this);
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}