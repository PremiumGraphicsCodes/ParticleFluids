#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ObjectRenderer.h"
#include "ObjectIdRenderer.h"

#include "../Scene/ViewModel.h"

#include "../Util/UnCopyable.h"

#include "../Shader/TextureObjectRepository.h"

namespace Crystal {
	namespace UI {
		class ViewModel;

class Renderer : private UnCopyable
{
public:
	explicit Renderer(Graphics::ICamera* camera);

	~Renderer() {}

	bool build(Shader::ShaderObjectRepository& shaders, Shader::TextureObjectRepository& textures);

	void render(const int width, const int height, const Shader::TextureObjectRepository& textures);

	void setViewModel(ViewModel& vm) {
		const auto& ovm = vm.object;
		objectRenderer.setViewModel(ovm);

		const auto& idvm = vm.objectId;
		objectIdRenderer.setViewModel(idvm);
	}

	ObjectRenderer* getObjectRenderer() { return &objectRenderer; }

	ObjectIdRenderer* getObjectIdRenderer() { return &objectIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
	ObjectRenderer objectRenderer;
	ObjectIdRenderer objectIdRenderer;
	bool showOffScreen;
};

	}
}