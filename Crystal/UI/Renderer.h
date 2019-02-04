#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

namespace Crystal {
	namespace UI {
		class ViewModel;

class Renderer
{
public:
	Renderer()
	{
	}

	~Renderer() {}

	bool build();

	void render(const int width, const int height, Shader::ITextureObject* texture);

	//void setViewModel(const ViewModel& vm);

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
};

	}
}