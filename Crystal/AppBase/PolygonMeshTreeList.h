#pragma once

#include "ITreeList.h"

namespace Crystal {
	namespace UI {

class PolygonMeshTreeList : public ITreeList
{
public:
	PolygonMeshTreeList(const std::string& name, Repository* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
};

	}
}