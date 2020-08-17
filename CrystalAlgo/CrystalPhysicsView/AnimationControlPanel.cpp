#include "AnimationControlPanel.h"

using namespace Crystal::UI;

AnimationControlPanel::AnimationControlPanel(const std::string& name, Scene::World* world, Canvas* canvas) :
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

void AnimationControlPanel::onStart()
{

}

void AnimationControlPanel::onStop()
{

}

void AnimationControlPanel::onReset()
{

}