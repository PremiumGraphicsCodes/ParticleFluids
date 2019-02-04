#include "Renderer.h"
#include "../../Crystal/UI/ObjectViewModel.h"

#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

Renderer::Renderer(Crystal::Graphics::ICamera* camera) :
	objectRenderer(camera),
	objectIdRenderer(camera)
{
}

bool Renderer::build()
{
	if (!objectRenderer.build()) {
		return false;
	}
	if (!objectIdRenderer.build()) {
		return false;
	}

	if (!renderer.build()) {
		return false;
	}
	return true;
}

void Renderer::render(const int width, const int height)
{
	objectRenderer.render();
	objectIdRenderer.render();

	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto texture = objectRenderer.getTexture();
	renderer.render(*texture);
}