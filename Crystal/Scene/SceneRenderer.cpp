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
using namespace Crystal::UI;

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
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (auto s : particleScenes) {
			pointRenderer.setBuffer(s->getGLBuffer());
			pointRenderer.render(*camera);

		}
	}
	if (mask.showLines) {
		for (auto s : wfScenes) {
			wireRenderer.setBuffer(s->getGLBuffer());
			wireRenderer.render(*camera);
		}
	}
	if (mask.showTrianlges) {
		std::vector<Material> materials;
		for (auto mat : materialScenes) {
			materials.push_back(*mat->getMaterial());
		}
		smoothRenderer.setMaterials(materials);
		std::vector<PointLight> lights;
		for (auto l : lightScenes) {
			lights.push_back(*l->getLight());
		}
		smoothRenderer.setLights(lights);
		std::vector<TextureObject> textures;
		for (auto tex : textureScenes) {
			textures.push_back(tex->getTextureObject());
		}
		smoothRenderer.setTextures(textures);
		for (auto pm : pmScenes) {
			const auto& bs = pm->getGLBuffers();
			for (auto b : bs) {
				smoothRenderer.setBuffer(b);
				smoothRenderer.render(*camera);
			}
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}