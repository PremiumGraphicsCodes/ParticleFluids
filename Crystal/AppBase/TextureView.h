#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace UI {

class TextureView : public IWindow
{
public:
	TextureView(const std::string& name, const Graphics::Image& image);

	~TextureView();

	void show() override;

	void setValue(const Graphics::Image& image);

	Graphics::Image getValue() const { return image; }

private:
	Graphics::Image image;
	GLuint textureId;
};

	}
}