#pragma once

#include "ITreeList.h"

namespace Crystal {
	namespace UI {

class PolygonTreeList : public ITreeList
{
public:
	PolygonTreeList(const std::string& name, Model* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
};

	}
}