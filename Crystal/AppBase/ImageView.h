#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace UI {

class ImageView : public IWindow
{
public:
	ImageView(const std::string& name, const Graphics::Image& image);

	~ImageView();

	void show() override;

	void setValue(const Graphics::Image& image);

	Graphics::Image getValue() const { return image; }

private:
	Graphics::Image image;
	GLuint textureId;
};

	}
}