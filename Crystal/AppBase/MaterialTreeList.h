#pragma once

#include "ITreeList.h"
#include "MaterialEditButton.h"

namespace Crystal {
	namespace UI {

class MaterialTreeList : public ITreeList
{
public:
	MaterialTreeList(const std::string& name, Repository* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
	MaterialEditView editButton;
};

	}
}