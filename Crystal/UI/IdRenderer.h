#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

namespace Crystal {
	namespace UI {
		class ViewModel;

class IdRenderer
{
public:
	IdRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~IdRenderer() {}

	bool build();

	void render(const int width, const int height);

	void setViewModel(const ViewModel& vm);

private:
	Shader::PointRenderer pointIdRenderer;

	Graphics::ICamera* camera;
	Shader::TextureObject texture;

};
	}
}