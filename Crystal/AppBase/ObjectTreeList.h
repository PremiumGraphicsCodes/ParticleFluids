#pragma once

#include "ITreeList.h"

namespace Crystal {
	namespace UI {

class ObjectTreeList : public ITreeList
{
public:
	ObjectTreeList(const std::string& name, Model* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
};
	}
}