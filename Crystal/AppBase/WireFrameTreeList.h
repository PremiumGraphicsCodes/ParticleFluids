#pragma once

#include "ITreeList.h"

namespace Crystal {
	namespace UI {

class WireFrameTreeList : public ITreeList
{
public:
	WireFrameTreeList(const std::string& name, Model* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
};

	}
}