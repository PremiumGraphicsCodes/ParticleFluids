#pragma once

#include "../../CrystalViewer/AppBase/IPanel.h"
#include "../../CrystalViewer/AppBase/Button.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

namespace Crystal {
	namespace UI {

class AnimationControlPanel : public IPanel
{
public:
	AnimationControlPanel(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	Button startButton;
	Button stopButton;
	Button resetButton;
	DirectoryView directoryView;

	void onStart();

	void onStop();

	void onReset();
};

	}
}