#pragma once

#include "IPopupButton.h"

#include "TextureView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class TextureAddButton : public IPopupButton
{
public:
	TextureAddButton(const std::string& name, Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	//TextureView texture;
	StringView name;
};

	}
}

