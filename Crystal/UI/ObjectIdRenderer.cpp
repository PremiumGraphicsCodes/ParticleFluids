#include "ObjectIdRenderer.h"
#include "../../Crystal/Scene/Scene.h"
#include "../../Crystal/Scene/SceneIdViewModel.h"
#include "../../Crystal/Scene/TextureScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

bool ObjectIdRenderer::build(IScene* scene, SceneFactory* factory)
{
	if (!pointIdRenderer.build()) {
		return false;
	}
	if (!lineIdRenderer.build()) {
		return false;
	}
	if (!triangleIdRenderer.build()) {
		return false;
	}

	frameBufferObject.build(512, 512);

	return true;
}


void ObjectIdRenderer::setViewModel(const SceneIdViewModel& vm)
{
	this->pointIdRenderer.setBuffer(vm.getPointIdBuffer());
	this->lineIdRenderer.setBuffer(vm.getLindIdBuffer(), 1.0f);
	this->triangleIdRenderer.setBuffer(vm.getTriangleIdBuffer());
}

DrawableID ObjectIdRenderer::getId(const double x, const double y, const TextureObject& texture)
{
	return getIdInTexCoord(x * texture.getWidth(), y * texture.getHeight(), texture);
}

DrawableID ObjectIdRenderer::getIdInTexCoord(const int x, const int y, const TextureObject& texture)
{
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	const auto& color = frameBufferObject.getColor(x, y);
	frameBufferObject.unbind();
	return DrawableID(color);
}

void ObjectIdRenderer::render(const TextureObject& texture)
{
	frameBufferObject.setTexture(texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointIdRenderer.render(*camera);
	lineIdRenderer.render(*camera);
	triangleIdRenderer.render(*camera);

	frameBufferObject.unbind();
}