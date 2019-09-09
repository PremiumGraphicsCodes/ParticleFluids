#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace UI {

class ColorRGBAView : public IWindow
{
public:
	ColorRGBAView(const std::string& name, const Graphics::ColorRGBAf& v) :
		IWindow(name)
	{
		setValue(v);
	}

	void onShow() override
	{
		ImGui::ColorEdit4(name.c_str(), value);
	}

	Graphics::ColorRGBAf getValue() const { return Graphics::ColorRGBAf(value[0], value[1], value[2], value[3]); }

	void setValue(const Graphics::ColorRGBAf& v)
	{
		value[0] = v.r;
		value[1] = v.g;
		value[2] = v.b;
		value[3] = v.a;
	}

private:
	float value[4];
};

	}
}