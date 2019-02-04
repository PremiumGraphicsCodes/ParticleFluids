#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ObjectRenderer.h"
#include "ObjectIdRenderer.h"

namespace Crystal {
	namespace UI {
		class ObjectViewModel;

class Renderer
{
public:
	Renderer(Graphics::ICamera* camera);

	~Renderer() {}

	bool build();

	void render(const int width, const int height);

	void setViewModel(const ObjectViewModel& vm) { objectRenderer.setViewModel(vm); }

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
	ObjectRenderer objectRenderer;
	ObjectIdRenderer objectIdRenderer;
};

	}
}