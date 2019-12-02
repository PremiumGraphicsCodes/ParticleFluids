#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "SceneRenderer.h"
#include "SceneIdRenderer.h"

#include "../Scene/ViewModel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class Renderer : private UnCopyable
{
public:
	Renderer();

	~Renderer() {}

	bool build();

	void render(const int width, const int height, const Scene::ViewModel& vm);

	SceneRenderer* getObjectRenderer() { return &objectRenderer; }

	SceneIdRenderer* getParentIdRenderer() { return &parentIdRenderer; }

	SceneIdRenderer* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::ICamera* getCamera() { return camera.get(); }

private:
	Shader::OnScreenRenderer renderer;

	SceneRenderer objectRenderer;
	SceneIdRenderer parentIdRenderer;
	SceneIdRenderer childIdRenderer;

	bool showOffScreen;

	std::unique_ptr<Graphics::ICamera> camera;
};

	}
}