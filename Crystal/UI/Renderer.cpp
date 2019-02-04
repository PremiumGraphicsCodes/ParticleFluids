#include "Renderer.h"
#include "../../Crystal/UI/ViewModel.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

bool Renderer::build()
{
	if (!renderer.build()) {
		return false;
	}

	Image image(2, 2);
	image.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
	image.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
	image.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));

	texture.create(image, 0);
	return true;
}

void Renderer::render(const int width, const int height)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.render(texture);
}