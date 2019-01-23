#pragma once

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

namespace Crystal {
	namespace UI {
		class ViewModel3d;

class Renderer
{
public:
	Renderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~Renderer() {}

	bool build();

	void render(const int width, const int height);

	void setViewModel(const ViewModel3d& vm);

private:
	Shader::PointRenderer pointRenderer;
	Shader::WireFrameRenderer wireRenderer;
	Shader::SmoothRenderer smoothRenderer;

	Graphics::ICamera* camera;
	Shader::TextureObject texture;

};
	}
}