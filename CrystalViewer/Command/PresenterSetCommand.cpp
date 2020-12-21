#include "PresenterSetCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Scene/PMSmoothPresenter.h"
#include "../../Crystal/Scene/PMAsWFPresenter.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

//#include "ShaderSendCommand.h"

#include "Public/PresenterSetLabels.h"

PresenterSetCommand::Args::Args() :
	id(PresenterSetLabels::IdLabel, 0),
	presenterName(PresenterSetLabels::PresenterNameLabel, std::string(""))
{
	add(&id);
}

std::string PresenterSetCommand::getName()
{
	return PresenterSetLabels::CommandNameLabel;
}

bool PresenterSetCommand::execute(World* world)
{
	auto s = world->getScenes()->findSceneById(std::any_cast<int>(args.id.getValue()));
	if (s->getType() == SceneType::PolygonMeshScene) {
		auto scene = static_cast<PolygonMeshScene*>(s);
		const auto name = args.presenterName.getValue();
		scene->getPresenter()->removeView(world->getRenderer(), *world->getGLFactory());
		if (name == "Smooth") {
			auto presenter = std::make_unique<PMSmoothPresenter>(scene);
			scene->setPresenter(std::move(presenter));
		}
		else if (name == "Wire") {
			auto presenter = std::make_unique<PMAsWFPresenter>(scene);
			scene->setPresenter(std::move(presenter));
		}
		scene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	}
	return true;
}