#include "ShaderSendCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ShaderSendCommand::Args::Args() :
	id("Id", 0)
{
	add(&id);
}

std::string ShaderSendCommand::getName()
{
	return "ShaderSend";
}

bool ShaderSendCommand::execute(World* world)
{
	auto s = world->getObjects()->findSceneById(std::any_cast<int>(args.id.getValue()));
	s->getController()->createView(world->getRenderer(), *world->getGLFactory());
	return true;
}

