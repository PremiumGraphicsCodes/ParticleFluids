#pragma once

#include "../Scene/PointRenderer.h"
#include "../Scene/LineRenderer.h"
#include "../Scene/SmoothRenderer.h"

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

	void render(const Scene::SceneViewModel& vm, const Shader::TextureObject& texture);

private:
	Scene::PointRenderer pointRenderer;
	Scene::LineRenderer wireRenderer;
	Scene::SmoothRenderer smoothRenderer;

	Graphics::ICamera* camera;

	Shader::FrameBufferObject frameBufferObject;
};
	}
}