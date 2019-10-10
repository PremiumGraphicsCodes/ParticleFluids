#pragma once

#include "IWindow.h"

#include "IntView.h"
#include "../../Crystal/Scene/WireFrameScene.h"

namespace Crystal {
	namespace UI {

class WireFrameView : public IWindow
{
public:
	explicit WireFrameView(const std::string& name);

	void onShow() override;

	void setValue(Scene::WireFrameScene* value);

private:
	IntView edgeCount;
};

	}
}