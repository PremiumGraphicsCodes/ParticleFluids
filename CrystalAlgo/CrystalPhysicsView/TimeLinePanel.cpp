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
	reader.setDirectryPath(directoryPath);
	getWorld()->addAnimation(&reader);
}

void TimeLinePanel::onStop()
{
	//getWorld()->removeAnimation(&reader);
}

void TimeLinePanel::onReset()
{
	reader.reset();
}