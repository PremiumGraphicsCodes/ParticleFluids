#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBuffer.h"

namespace Crystal {
	namespace UI {
		class ObjectViewModel;

class ObjectRenderer
{
public:
	ObjectRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~ObjectRenderer() {}

	bool build();

	void render(const int width, const int height);

	void setViewModel(const ObjectViewModel& vm);

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