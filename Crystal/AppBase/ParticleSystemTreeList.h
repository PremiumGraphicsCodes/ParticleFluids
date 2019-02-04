#pragma once

#include "ITreeList.h"

namespace Crystal {
	namespace UI {

class ParticleSystemTreeList : public ITreeList
{
public:
	ParticleSystemTreeList(const std::string& name, Repository* model, Canvas* canvas);

	void show() override {
		onShow();
	}

	void onShow() override;

private:
};
	}
}