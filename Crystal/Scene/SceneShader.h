#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ScreenShader.h"
#include "ScreenIdShader.h"

#include "ScreenShaderScene.h"
#include "ScreenIdShaderScene.h"

#include "SceneShaderScene.h"

#include "IShaderScene.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class SceneShader : public IShaderScene
{
public:
	SceneShader();

	~SceneShader() {}

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override {};

	void render() override;

	void render(const int width, const int height);

	ScreenShader* getObjectRenderer() { return &objectRenderer; }

	ScreenIdShader* getParentIdRenderer() { return &parentIdRenderer; }

	ScreenIdShader* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::Camera* getCamera() { return camera.get(); }

	SceneShaderScene* getScene() { return &scene; }

private:
	Shader::OnScreenRenderer renderer;

	ScreenShader objectRenderer;
	ScreenIdShader parentIdRenderer;
	ScreenIdShader childIdRenderer;

	SceneShaderScene scene;

	bool showOffScreen;

	std::unique_ptr<Graphics::Camera> camera;
};

	}
}