#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ScreenShader.h"
#include "ScreenIdShader.h"

#include "ScreenShaderBuffer.h"
#include "ScreenIdShaderBuffer.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

struct ShaderBuffer
{
	ScreenShaderBuffer screen;
	ScreenIdShaderBuffer parentId;
	ScreenIdShaderBuffer childId;
};

class ShaderScene : private UnCopyable
{
public:
	ShaderScene();

	~ShaderScene() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(const int width, const int height);

	ScreenShader* getObjectRenderer() { return &objectRenderer; }

	ScreenIdShader* getParentIdRenderer() { return &parentIdRenderer; }

	ScreenIdShader* getChildIdRenderer() { return &childIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

	Graphics::Camera* getCamera() { return camera.get(); }

	ShaderBuffer* getBuffer() { return &buffer; }

private:
	Shader::OnScreenRenderer renderer;

	ScreenShader objectRenderer;
	ScreenIdShader parentIdRenderer;
	ScreenIdShader childIdRenderer;

	ShaderBuffer buffer;

	bool showOffScreen;

	std::unique_ptr<Graphics::Camera> camera;
};

	}
}