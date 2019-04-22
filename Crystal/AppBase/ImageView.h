#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace UI {

class ImageView : public IWindow
{
public:
	ImageView(const std::string& name, const Graphics::Image& image) :
		IWindow(name),
		image(image)
	{}

	void show() override;

private:
	Graphics::Image image;
};

	}
}