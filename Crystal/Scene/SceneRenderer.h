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
	SceneRenderer() :
		pointRenderer(-1, "PointRenderer"),
		wireRenderer(-1, "LineRenderer"),
		smoothRenderer(-1, "SmoothRenderer")
	{
	}

	~SceneRenderer() {}

	bool build();

	void render(Graphics::ICamera* camera, const Scene::SceneViewModel& vm);

	struct Mask
	{
		Mask() :
			showPoints(true),
			showLines(true),
			showTrianlges(true)
		{}

		bool showPoints;
		bool showLines;
		bool showTrianlges;
	};

	void setMask(const Mask& mask) { this->mask = mask; }

	Mask getMask() const { return mask; }

	Shader::TextureObject* getTexture() { return &texture; }

private:
	Scene::PointRenderer pointRenderer;
	Scene::LineRenderer wireRenderer;
	Scene::SmoothRenderer smoothRenderer;

	Mask mask;

	Graphics::ICamera* camera;

	Shader::TextureObject texture;
	Shader::FrameBufferObject frameBufferObject;
};
	}
}