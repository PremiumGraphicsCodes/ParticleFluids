#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBuffer.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {
		class ObjectViewModel;
		class AppearanceViewModel;

class ObjectRenderer : private UnCopyable
{
public:
	ObjectRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~ObjectRenderer() {}

	bool build();

	void render(const Shader::TextureObject& texture, const Shader::TextureObject& smoothTexture);

	void setViewModel(const ObjectViewModel& vm, const AppearanceViewModel& avm);

private:
	Shader::PointRenderer pointRenderer;
	Shader::WireFrameRenderer wireRenderer;
	Shader::SmoothRenderer smoothRenderer;

	std::vector<Shader::SmoothRenderer::Buffer> smoothBuffers;

	Graphics::ICamera* camera;

	Shader::FrameBuffer frameBufferObject;
};
	}
}