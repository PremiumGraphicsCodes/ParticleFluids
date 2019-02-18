#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ObjectRenderer.h"
#include "ObjectIdRenderer.h"

#include "ViewModel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {
		class ViewModel;

class Renderer : private UnCopyable
{
public:
	Renderer(Graphics::ICamera* camera);

	~Renderer() {}

	bool build();

	void render(const int width, const int height, const TextureObjectRepository& textures);

	void setViewModel(ViewModel& vm) {
		const auto& ovm = vm.object;
		const auto& avm = vm.appearance;
		objectRenderer.setViewModel(ovm, avm);

		const auto& idvm = vm.objectId;
		objectIdRenderer.setViewModel(idvm);
	}

	ObjectRenderer* getObjectRenderer() { return &objectRenderer; }

	ObjectIdRenderer* getObjectIdRenderer() { return &objectIdRenderer; }

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
	ObjectRenderer objectRenderer;
	ObjectIdRenderer objectIdRenderer;
};

	}
}