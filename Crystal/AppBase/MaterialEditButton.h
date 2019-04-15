#pragma once

#include "IPopupButton.h"
#include "MaterialView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class MaterialEditButton : public IPopupButton
{
public:
	MaterialEditButton(Repository* model, Canvas* canvas);

	void setValue(const int id, const Graphics::Material& material, const std::string& name) {
		this->id.setValue(id);
		this->material.setValue(material);
		this->name.setValue( name );
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	IntView id;
	MaterialView material;
	StringView name;
};

	}
}
