#pragma once

#include "IPopupButton.h"
#include "LightView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class LightEditButton : public IPopupButton
{
public:
	LightEditButton(Repository* model, Canvas* canvas);

	/*
	void setValue(const Graphics::PointLight& material, const std::string& name) {
		this->light.setValue(material);
		this->name.setValue(name);
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}
	*/

private:
	LightView light;
	StringView name;
};

	}
}
