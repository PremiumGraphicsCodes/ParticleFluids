#include "ScreenShaderScene.h"

#include "../Shader/GLObjectFactory.h"

#include "ScreenShaderBuffer.h"

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

void ScreenShaderScene::render(Camera* camera, const ScreenShaderBuffer& buffer)
{
	this->camera = camera;
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (auto buffer : buffer.pointBuffers) {
			buffer.camera = *camera;
			pointRenderer.send(buffer);
			pointRenderer.render();
		}
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
		std::vector<Shader::TextureObject> textures;
		for (auto tex : buffer.textureScenes) {
			textures.push_back(tex->getTextureObject());
		}
		for (auto pm : buffer.pmScenes) {
	//		smoothRenderer.send();
			smoothRenderer.render();
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}