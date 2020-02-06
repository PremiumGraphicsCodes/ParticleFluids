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
	namespace Shader {
		class GLObjectFactory;
	}
	namespace UI {


class SceneRenderer : private UnCopyable
{
public:
	SceneRenderer()
	{
	}

	~SceneRenderer() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(Graphics::Camera* camera, const Scene::SceneViewModel& vm);

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

	Shader::TextureObject* getTexture() { return texture.get(); }

private:
	Scene::PointRenderer pointRenderer;
	Scene::LineRenderer wireRenderer;
	Scene::SmoothRenderer smoothRenderer;

	Scene::PointRenderer::GLBuffer pointBuffer;

	Mask mask;

	Graphics::Camera* camera;

	std::unique_ptr< Shader::TextureObject > texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;
};
	}
}