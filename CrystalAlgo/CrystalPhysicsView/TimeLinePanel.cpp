#include "TimeLinePanel.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
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
	auto shape = std::make_unique < Crystal::Shape::ParticleSystem<ParticleAttribute> >();
	ParticleAttribute attr;
	attr.color = ColorRGBAf(0, 0, 0, 0);
	attr.size = 10.0f;
	for (int i = 0; i < 10000; ++i) {
		shape->add(Vector3dd(0, 0, 0), attr);
	}
	this->psScene = new ParticleSystemScene(getWorld()->getNextSceneId(), "KFFluid", std::move(shape));
	getWorld()->getScenes()->addScene(psScene);

	auto presenter = psScene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	presenter->setBlend(false);

	const auto directoryPath = directoryView.getPath();
	reader.setDirectryPath(directoryPath);
	animator.setReader(&reader);
	animator.setScene(psScene);
	getWorld()->addAnimation(&animator);
}

void TimeLinePanel::onStop()
{
	//getWorld()->removeAnimation(&reader);
}

void TimeLinePanel::onReset()
{
	reader.reset();
}