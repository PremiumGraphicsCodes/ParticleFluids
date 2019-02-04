#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ObjectRenderer.h"
#include "ObjectIdRenderer.h"

#include "ViewModel.h"

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

	void setViewModel(ViewModel& vm) {
		const auto& ovm = vm.object;
		const auto& avm = vm.appearance;
		objectRenderer.setViewModel(ovm, avm);

		const auto& idvm = vm.objectId;
		objectIdRenderer.setViewModel(idvm);
	}

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
	ObjectRenderer objectRenderer;
	ObjectIdRenderer objectIdRenderer;
};

	}
}