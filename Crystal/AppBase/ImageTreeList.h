#pragma once

#include "ITreeList.h"
//#include "LightEditButton.h"

namespace Crystal {
	namespace UI {

class ImageTreeList : public ITreeList
{
public:
	ImageTreeList(const std::string& name, Repository* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
	//LightEditButton edit;
};

	}
}