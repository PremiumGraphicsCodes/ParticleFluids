#include "ObjectIdRenderer.h"
#include "../../Crystal/UI/IdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

bool ObjectIdRenderer::build()
{
	if (!pointIdRenderer.build()) {
		return false;
	}

	return true;
}

void ObjectIdRenderer::setViewModel(const IdViewModel& vm)
{
	this->pointIdRenderer.setBuffer(vm.getPointIdBuffer());
}

void ObjectIdRenderer::render(const int width, const int height)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointIdRenderer.render(*camera);
}