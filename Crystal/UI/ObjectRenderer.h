#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {
		class ObjectViewModel;

class ObjectRenderer : private UnCopyable
{
public:
	ObjectRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~ObjectRenderer() {}

	bool build(Shader::ShaderObjectRepository& shaders);

	void render(const Shader::TextureObject& texture, const Shader::TextureObject& smoothTexture);

	void setViewModel(const ObjectViewModel& vm);

private:
	Shader::PointRenderer pointRenderer;
	Shader::LineRenderer wireRenderer;
	Shader::SmoothRenderer smoothRenderer;

	std::vector<Shader::SmoothRenderer::Buffer> smoothBuffers;

	Graphics::ICamera* camera;

	Shader::FrameBufferObject frameBufferObject;
};
	}
}