#pragma once

#include "../Scene/PointShaderScene.h"
#include "../Scene/LineShaderScene.h"
#include "../Scene/SmoothShaderScene.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {
		class SceneViewModel;
	}
	namespace UI {

class SceneRenderer : private UnCopyable
{
public:
	SceneRenderer(Graphics::ICamera* camera) :
		camera(camera),
		pointRenderer(-1, "PointRenderer"),
		wireRenderer(-1, "LineRenderer"),
		smoothRenderer(-1, "SmoothRenderer")
	{
	}

	~SceneRenderer() {}

	bool build();

	void render(const Scene::SceneViewModel& vm, const Shader::TextureObject& texture, const Shader::TextureObject& smoothTexture);

private:
	Scene::PointShaderScene pointRenderer;
	Scene::LineShaderScene wireRenderer;
	Scene::SmoothShaderScene smoothRenderer;

	Graphics::ICamera* camera;

	Shader::FrameBufferObject frameBufferObject;
};
	}
}