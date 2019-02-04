#pragma once

#include "../Shader/TextureObject.h"
#include "ObjectRenderer.h"
#include "../Shader/OnScreenRenderer.h"

namespace Crystal {
	namespace UI {
		class ViewModel;

class Renderer
{
public:
	Renderer(Graphics::ICamera* camera);

	~Renderer() {}

	bool build();

	void render(const int width, const int height);

	void setViewModel(const ViewModel& vm) { objectRenderer.setViewModel(vm); }

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
	ObjectRenderer objectRenderer;
};

	}
}