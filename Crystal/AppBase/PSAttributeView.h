#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"

#include "../UI/ParticleAttribute.h"

namespace Crystal {
	namespace UI {

class PSAttributeView : public IWindow
{
public:
	PSAttributeView(const std::string& name) :
		IWindow(name),
		size("Size", 1.0f),
		color("Color")
		//nameView("Name", "WireFrame")
	{
	}

	void show() override
	{
		size.show();
		color.show();
		//nameView.show();
		//ImGui::ColorPicker4("Color", &color[0]);
	}

	UI::ParticleAttribute getValue() const {
		UI::ParticleAttribute attr;
		attr.size = size.getValue();
		attr.color = color.getValue();
		return attr;
	}

private:
	FloatView size;
	Float4View color;
	//StringView nameView;
};

	}
}

