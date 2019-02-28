#pragma once

#include "IPopupButton.h"
#include "../UI/WireFrameAttribute.h"

namespace Crystal {
	namespace UI {

class WFAttributeButton : public IPopupButton
{
public:
	WFAttributeButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		width(1.0f),
		color(0,0,0,0)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

	UI::WireFrameAttribute getValue() const {
		UI::WireFrameAttribute attr;
		attr.width = width;
		attr.color = color;
		return attr;
	}

private:
	float width;
	glm::vec4 color;
};

	}
}

