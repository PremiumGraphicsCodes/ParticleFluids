#pragma once

#include "IPopupButton.h"

#include "MaterialView.h"

namespace Crystal {
	namespace UI {

class TextureAddButton : public IPopupButton
{
public:
	TextureAddButton(const std::string& name, Repository* model, Canvas* canvas);

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

