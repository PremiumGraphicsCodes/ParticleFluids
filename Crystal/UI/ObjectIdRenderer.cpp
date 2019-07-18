#include "ObjectIdRenderer.h"
#include "../../Crystal/Scene/SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

bool ObjectIdRenderer::build(ShaderObjectRepository& shaders, TextureObjectRepository& textures)
{
	if (!pointIdRenderer.build(shaders)) {
		return false;
	}
	if (!lineIdRenderer.build(shaders)) {
		return false;
	}
	if (!triangleIdRenderer.build(shaders)) {
		return false;
	}

	const auto id = textures.add(Image(512, 512), "IdTexture");
	this->texture = textures.findObjectById(id);

	//Image image(512, 512);
	//texture.create(image, 0);

	frameBufferObject.build(512, 512);

	return true;
}

void ObjectIdRenderer::setViewModel(const SceneIdViewModel& vm)
{
	this->pointIdRenderer.setBuffer(vm.getPointIdBuffer());
	this->lineIdRenderer.setBuffer(vm.getLindIdBuffer(), 1.0f);
	this->triangleIdRenderer.setBuffer(vm.getTriangleIdBuffer());
}

DrawableID ObjectIdRenderer::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture->getWidth(), y * texture->getHeight());
}

DrawableID ObjectIdRenderer::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject.bind();
	glViewport(0, 0, texture->getWidth(), texture->getHeight());
	const auto& color = frameBufferObject.getColor(x, y);
	frameBufferObject.unbind();
	return DrawableID(color);
}

void ObjectIdRenderer::render()
{
	frameBufferObject.setTexture(*texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture->getWidth(), texture->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointIdRenderer.render(*camera);
	lineIdRenderer.render(*camera);
	triangleIdRenderer.render(*camera);

	frameBufferObject.unbind();
}