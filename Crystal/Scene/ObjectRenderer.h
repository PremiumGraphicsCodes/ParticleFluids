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

class ObjectRenderer : private UnCopyable
{
public:
	ObjectRenderer(Graphics::ICamera* camera) :
		camera(camera),
		pointRenderer(-1, "PointRenderer"),
		wireRenderer(-1, "LineRenderer"),
		smoothRenderer(-1, "SmoothRenderer")
	{
	}

	~ObjectRenderer() {}

	bool build();

	void render(const Shader::TextureObject& texture, const Shader::TextureObject& smoothTexture);

	void setViewModel(const Scene::SceneViewModel& vm);

private:
	Scene::PointShaderScene pointRenderer;
	Scene::LineShaderScene wireRenderer;
	Scene::SmoothShaderScene smoothRenderer;

	std::vector<Scene::SmoothTriangleBuffer> smoothBuffers;

	Graphics::ICamera* camera;

	Shader::FrameBufferObject frameBufferObject;
};
	}
}