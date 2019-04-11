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
