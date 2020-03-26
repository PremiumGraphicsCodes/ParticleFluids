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

struct ShaderBuffer
{
	ScreenShaderBuffer screen;
};

class ShaderScene : private UnCopyable
{
public:
	ShaderScene();

	~ShaderScene() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(const int width, const int height, const ViewModel& vm);

	ScreenShaderScene* getObjectRenderer() { return &objectRenderer; }

	ScreenIdShaderScene* getParentIdRenderer() { return &parentIdRenderer; }

	ScreenIdShaderScene* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::Camera* getCamera() { return camera.get(); }

	ShaderBuffer* getBuffer() { return &buffer; }

private:
	Shader::OnScreenRenderer renderer;

	ScreenShaderScene objectRenderer;
	ScreenIdShaderScene parentIdRenderer;
	ScreenIdShaderScene childIdRenderer;

	ShaderBuffer buffer;

	bool showOffScreen;

	std::unique_ptr<Graphics::Camera> camera;
};

	}
}