#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"

#include "../Scene/ParticleAttribute.h"

namespace Crystal {
	namespace UI {

class PSAttributeView : public IWindow
{
public:
	PSAttributeView(const std::string& name) :
		IWindow(name),
		size("Size", 10.0f),
		color("Color", glm::vec4(1,1,1,1))
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

	Scene::ParticleAttribute getValue() const {
		Scene::ParticleAttribute attr;
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

