#include "PresenterSetCommand.h"

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
	/*
	s->getPresenter()->updateView();
	*/
	return true;
}

