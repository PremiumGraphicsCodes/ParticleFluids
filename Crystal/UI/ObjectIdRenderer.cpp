#include "ObjectIdRenderer.h"
#include "../../Crystal/UI/IdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

bool ObjectIdRenderer::build()
{
	if (!pointIdRenderer.build()) {
		return false;
	}

	Image image(512, 512);
	texture.create(image, 0);

	frameBufferObject.build(512, 512);

	return true;
}

void ObjectIdRenderer::setViewModel(const IdViewModel& vm)
{
	this->pointIdRenderer.setBuffer(vm.getPointIdBuffer());
}

void ObjectIdRenderer::render(const int width, const int height)
{
	frameBufferObject.setTexture(texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointIdRenderer.render(*camera);

	frameBufferObject.unbind();
}