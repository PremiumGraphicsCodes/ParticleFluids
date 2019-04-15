#pragma once

#include "IPopupButton.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class LightEditButton : public IPopupButton
{
public:
	LightEditButton(Repository* model, Canvas* canvas);

	void setValue(const Graphics::PointLight& light, const std::string& name) {
		this->light.setValue(light);
		this->name.setValue(name);
	}
/*
	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}
	*/

private:
	IntView id;
	LightView light;
	StringView name;
};

	}
}
