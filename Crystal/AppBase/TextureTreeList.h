#pragma once

#include "ITreeList.h"
#include "ImageView.h"

namespace Crystal {
	namespace UI {

class TextureTreeList : public ITreeList
{
public:
	TextureTreeList(const std::string& name, Repository* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
	ImageView image;
};

	}
}