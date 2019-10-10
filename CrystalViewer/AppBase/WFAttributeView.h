#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "ColorRGBAView.h"
#include "StringView.h"

#include "../../Crystal/Scene/WireFrameAttribute.h"

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

	void onShow() override
	{
		width.show();
		color.show();
		//nameView.show();
		//ImGui::ColorPicker4("Color", &color[0]);
	}

	Scene::WireFrameAttribute getValue() const {
		Scene::WireFrameAttribute attr;
		attr.width = width.getValue();
		attr.color = color.getValue();
		return attr;
	}

private:
	FloatView width;
	ColorRGBAView color;
	//StringView nameView;
};

	}
}

