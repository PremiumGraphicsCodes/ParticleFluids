#pragma once

#include "../../CrystalViewer/AppBase/IPanel.h"
#include "../../CrystalViewer/AppBase/Button.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"
#include "../CrystalPhysics/TimeSeriesParticleSystemReader.h"

namespace Crystal {
	namespace UI {

class TimeLinePanel : public IPanel
{
public:
	TimeLinePanel(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	Button startButton;
	Button stopButton;
	Button resetButton;
	DirectoryView directoryView;
	Physics::TimeSeriesParticleSystemReader reader;

	void onStart();

	void onStop();

	void onReset();
};

	}
}