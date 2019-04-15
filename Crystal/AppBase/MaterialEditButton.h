#pragma once

#include "IPopupButton.h"
#include "MaterialView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class MaterialEditButton : public IPopupButton
{
public:
	MaterialEditButton(Repository* model, Canvas* canvas);

	void setValue(const Graphics::Material& material, const std::string& name) {
		this->material.setValue(material);
		this->name.setValue( name );
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	MaterialView material;
	StringView name;
};

	}
}
