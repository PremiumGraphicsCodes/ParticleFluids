#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBuffer.h"

namespace Crystal {
	namespace UI {
		class IdViewModel;

class ObjectIdRenderer
{
public:
	ObjectIdRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~ObjectIdRenderer() {}

	bool build();

	void render(const int width, const int height);

	void setViewModel(const IdViewModel& vm);

private:
	Shader::PointRenderer pointIdRenderer;

	Shader::FrameBuffer frameBufferObject;
	Shader::TextureObject texture;

	Graphics::ICamera* camera;
};
	}
}