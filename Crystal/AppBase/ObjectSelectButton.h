#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

class ObjectSelectButton : public IPopupButton
{
public:
	ObjectSelectButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		id(0)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

	int getId() const { return id; }

private:
	int id;
};

	}
}