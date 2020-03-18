#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ScreenShaderScene.h"
#include "ScreenIdShaderScene.h"

#include "../Scene/ViewModel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class Renderer : private UnCopyable
{
public:
	Renderer();

	~Renderer() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(const int width, const int height, const ViewModel& vm);

	ScreenShaderScene* getObjectRenderer() { return &objectRenderer; }

	ScreenIdShaderScene* getParentIdRenderer() { return &parentIdRenderer; }

	ScreenIdShaderScene* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::Camera* getCamera() { return camera.get(); }

private:
	Shader::OnScreenRenderer renderer;

	ScreenShaderScene objectRenderer;
	ScreenIdShaderScene parentIdRenderer;
	ScreenIdShaderScene childIdRenderer;

	bool showOffScreen;

	std::unique_ptr<Graphics::Camera> camera;
};

	}
}