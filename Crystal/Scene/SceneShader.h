#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ScreenShader.h"
#include "ScreenIdShader.h"

#include "ScreenShaderScene.h"
#include "ScreenIdShaderScene.h"

#include "ShaderBuffer.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class SceneShader : private UnCopyable
{
public:
	SceneShader();

	~SceneShader() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(const int width, const int height);

	ScreenShader* getObjectRenderer() { return &objectRenderer; }

	ScreenIdShader* getParentIdRenderer() { return &parentIdRenderer; }

	ScreenIdShader* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::Camera* getCamera() { return camera.get(); }

	SceneShaderScene* getBuffer() { return &buffer; }

private:
	Shader::OnScreenRenderer renderer;

	ScreenShader objectRenderer;
	ScreenIdShader parentIdRenderer;
	ScreenIdShader childIdRenderer;

	SceneShaderScene buffer;

	bool showOffScreen;

	std::unique_ptr<Graphics::Camera> camera;
};

	}
}