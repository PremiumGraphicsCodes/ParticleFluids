#include "ShaderSendCommand.h"

#include "Public/ShaderSendLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ShaderSendCommand::Args::Args() :
	id(ShaderSendLabels::IdLabel, 0)
{
	add(&id);
}

std::string ShaderSendCommand::getName()
{
	return ShaderSendLabels::CommandNameLabel;
}

bool ShaderSendCommand::execute(World* world)
{
	auto s = world->getScenes()->findSceneById(std::any_cast<int>(args.id.getValue()));
	s->getController()->updateView();
	return true;
}

