#pragma once

#include "IPopupButton.h"
#include "../UI/WireFrameAttribute.h"
#include "FloatView.h"
#include "Float4View.h"

namespace Crystal {
	namespace UI {

class WFAttributeView : public IWindow
{
public:
	WFAttributeView(const std::string& name) :
		IWindow(name),
		width("Width", 1.0f),
		color("Color")
	{
	}

	void show() override
	{
		width.show();
		color.show();
		//ImGui::ColorPicker4("Color", &color[0]);
	}

	UI::WireFrameAttribute getValue() const {
		UI::WireFrameAttribute attr;
		attr.width = width.getValue();
		attr.color = color.getValue();
		return attr;
	}

private:
	FloatView width;
	Float4View color;
};

	}
}

