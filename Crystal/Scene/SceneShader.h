#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "ShaderRepository.h"
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

enum RenderTarget
{
	Shaded,
	ParentId,
	ChildId,
};

class SceneShader
{
public:
	SceneShader();

	~SceneShader() {}

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory){};

	void render(const Graphics::Camera& camera);

	void render(const Graphics::Camera& camera, const int width, const int height);

	ShaderRepository* getObjectRenderer() { return objectRenderer; }

	ScreenIdShader* getParentIdRenderer() { return parentIdRenderer; }

	ScreenIdShader* getChildIdRenderer() { return childIdRenderer; }

	void setRenderTarget(const RenderTarget target) { this->target = target; }

	SceneShaderScene* getScene() { return &scene; }

private:
	Shader::OnScreenRenderer renderer;

	ShaderRepository* objectRenderer;
	ScreenIdShader* parentIdRenderer;
	ScreenIdShader* childIdRenderer;

	SceneShaderScene scene;
	RenderTarget target;
};

	}
}