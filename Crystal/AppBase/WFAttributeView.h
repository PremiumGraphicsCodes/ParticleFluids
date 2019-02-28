#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"

#include "../UI/WireFrameAttribute.h"

namespace Crystal {
	namespace UI {

class WFAttributeView : public IWindow
{
public:
	WFAttributeView(const std::string& name) :
		IWindow(name),
		width("Width", 1.0f),
		color("Color", glm::vec4(0,0,0,0))
		//nameView("Name", "WireFrame")
	{
	}

	void show() override
	{
		width.show();
		color.show();
		//nameView.show();
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
	//StringView nameView;
};

	}
}

