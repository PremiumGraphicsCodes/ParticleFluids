#include "TimeLinePanel.h"

using namespace Crystal::UI;

TimeLinePanel::TimeLinePanel(const std::string& name, Scene::World* world, Canvas* canvas) :
	IPanel(name, world, canvas),
	startButton("Start"),
	stopButton("Stop"),
	resetButton("Reset"),
	directoryView("OutputDir")
{
	startButton.setFunction([=]() { onStart(); });
	stopButton.setFunction([=]() { onStop(); });
	resetButton.setFunction([=]() { onReset(); });

	add(&startButton);
	add(&stopButton);
	add(&resetButton);
	add(&directoryView);
}

void TimeLinePanel::onStart()
{
	const auto directoryPath = directoryView.getPath();
}

void TimeLinePanel::onStop()
{

}

void TimeLinePanel::onReset()
{

}