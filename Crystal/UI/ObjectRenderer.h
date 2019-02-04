#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBuffer.h"

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

	void render();

	void setViewModel(const ObjectViewModel& vm, const AppearanceViewModel& avm);

	Shader::TextureObject* getTexture() { return &texture; }

private:
	Shader::PointRenderer pointRenderer;
	Shader::WireFrameRenderer wireRenderer;
	Shader::SmoothRenderer smoothRenderer;

	Graphics::ICamera* camera;

	Shader::FrameBuffer frameBufferObject;
	Shader::TextureObject texture;

};
	}
}