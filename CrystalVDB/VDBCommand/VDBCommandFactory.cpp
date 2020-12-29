#include "VDBCommandFactory.h"

#include "VDBInitCommand.h"
#include "VDBFileWriteCommand.h"
#include "VDBFileReadCommand.h"
#include "VDBMeshCreateCommand.h"
#include "VDBParticleSystemToMeshCommand.h"

using namespace Crystal::Command;
using namespace Crystal::VDB;

std::unique_ptr<ICommand> VDBCommandFactory::createCommand(const std::string& name)
{
	if (name == VDBInitCommand::getName()) {
		return std::make_unique<VDBInitCommand>();
	}
	else if (name == VDBFileWriteCommand::getName()) {
		return std::make_unique<VDBFileWriteCommand>();
	}
	else if (name == VDBFileReadCommand::getName()) {
		return std::make_unique<VDBFileReadCommand>();
	}
	else if (name == VDBMeshCreateCommand::getName()) {
		return std::make_unique<VDBMeshCreateCommand>();
	}
	else if (name == VDBParticleSystemToMeshCommand::getName()) {
		return std::make_unique<VDBParticleSystemToMeshCommand>();
	}
	else {
		assert(false);
	}
	return nullptr;
}
