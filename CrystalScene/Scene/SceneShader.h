#pragma once

#include "Crystal/Shader/TextureObject.h"
#include "Crystal/Shader/OnScreenRenderer.h"

#include "ScreenShader.h"
#include "ScreenIdShader.h"

#include "IShaderScene.h"

#include "Crystal/Util/UnCopyable.h"
#include "RendererRepository.h"

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

	Shader::ShaderBuildStatus build();

	void release();

	void render(const Graphics::Camera& camera);

	void render(const Graphics::Camera& camera, const int width, const int height);

	ScreenShader* getObjectRenderer() { return objectRenderer; }

	ScreenIdShader* getParentIdRenderer() { return parentIdRenderer; }

	ScreenIdShader* getChildIdRenderer() { return childIdRenderer; }

	void setRenderTarget(const RenderTarget target) { this->target = target; }

	Shader::GLObjectFactory* getGLFactory() { return &glFactory; }

	RendererRepository* getRenderers() { return &renderers; }

private:
	ScreenShader* objectRenderer;
	ScreenIdShader* parentIdRenderer;
	ScreenIdShader* childIdRenderer;

	RendererRepository renderers;

	RenderTarget target;

	Shader::GLObjectFactory glFactory;
};

	}
}