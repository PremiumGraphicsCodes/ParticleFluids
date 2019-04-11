#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "Float4View.h"
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
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
	FloatView shininess;
	StringView name;
};

	}
}
