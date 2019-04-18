#include "ObjectIdRenderer.h"
#include "../../Crystal/UI/ObjectIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

bool ObjectIdRenderer::build()
{
	if (!pointIdRenderer.build()) {
		return false;
	}
	if (!lineIdRenderer.build()) {
		return false;
	}

	Image image(512, 512);
	texture.create(image, 0);

	frameBufferObject.build(512, 512);

	return true;
}

void ObjectIdRenderer::setViewModel(const ObjectIdViewModel& vm)
{
	this->pointIdRenderer.setBuffer(vm.getPointIdBuffer());
	this->lineIdRenderer.setBuffer(vm.getLindIdBuffer(), 1.0f);
}

DrawableID ObjectIdRenderer::getId(const double x, const double y)
{
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	const auto& color = frameBufferObject.getColor(x * texture.getWidth(), y * texture.getHeight());
	frameBufferObject.unbind();
	return DrawableID(color);
}

void ObjectIdRenderer::render()
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

	frameBufferObject.unbind();
}