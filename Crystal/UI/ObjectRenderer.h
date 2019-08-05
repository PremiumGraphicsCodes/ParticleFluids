#pragma once

#include "../Scene/PointShaderScene.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {
		class SceneViewModel;
	}
	namespace UI {

class ObjectRenderer : private UnCopyable
{
public:
	ObjectRenderer(Graphics::ICamera* camera) :
		camera(camera),
		pointRenderer(0, "PointRenderer")
	{
	}

	~ObjectRenderer() {}

	bool build();

	void render(const Shader::TextureObject& texture, const Shader::TextureObject& smoothTexture);

	void setViewModel(const Scene::SceneViewModel& vm);

private:
	Scene::PointShaderScene pointRenderer;
	Shader::LineRenderer wireRenderer;
	Shader::SmoothRenderer smoothRenderer;

	std::vector<Shader::SmoothRenderer::Buffer> smoothBuffers;

	Graphics::ICamera* camera;

	Shader::FrameBufferObject frameBufferObject;
};
	}
}