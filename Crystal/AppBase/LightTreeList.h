#pragma once

#include "ITreeList.h"

namespace Crystal {
	namespace UI {

class LightTreeList : public ITreeList
{
public:
	LightTreeList(const std::string& name, Repository* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
};

	}
}