#include "IPSAddView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IPSAddView::IPSAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	//matrixView("Matrix", Math::Identity()),
	attributeView("PSAttribute"),
	nameView("Name", "ParticleSystem01"),
	presenterView("Presenter"),
	doBlendView("Blend", false)
{
	//add(&matrixView);
	add(&attributeView);
	add(&nameView);
	add(&presenterView);
	add(&doBlendView);
}

void IPSAddView::addParticleSystem(const std::vector<Vector3dd>& positions)
{
	auto attr = attributeView.getValue();
	auto name = nameView.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), name, std::move(shape));
	getWorld()->getScenes()->addScene(scene);
	const auto newId = scene->getId();

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	presenter->setBlend(doBlendView.getValue());

	/*
	const auto boundingBox = getWorld()->getBoundingBox();
	auto camera = getWorld()->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, dist * 2.0, 0), boundingBox.getCenter(), Vector3dd(1, 0, 0));
	*/
}