#include "VDBCommandFactory.h"

#include "VDBInitCommand.h"
#include "VDBFileWriteCommand.h"
#include "VDBFileReadCommand.h"
#include "VDBOBJFileReadCommand.h"
#include "VDBOBJFileWriteCommand.h"
#include "VDBSceneCreateCommand.h"
#include "VDBParticleSystemToMeshCommand.h"
#include "VDBMeshToParticleSystemCommand.h"
#include "VDBMeshToVolumeCommand.h"

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
	else if (name == VDBOBJFileReadCommand::getName()) {
		return std::make_unique<VDBOBJFileReadCommand>();
	}
	else if (name == VDBOBJFileWriteCommand::getName()) {
		return std::make_unique<VDBOBJFileWriteCommand>();
	}
	else if (name == VDBSceneCreateCommand::getName()) {
		return std::make_unique<VDBSceneCreateCommand>();
	}
	else if (name == VDBParticleSystemToMeshCommand::getName()) {
		return std::make_unique<VDBParticleSystemToMeshCommand>();
	}
	else if (name == VDBMeshToParticleSystemCommand::getName()) {
		return std::make_unique<VDBMeshToParticleSystemCommand>();
	}
	else if (name == VDBMeshToVolumeCommand::getName()) {
		return std::make_unique<VDBMeshToVolumeCommand>();
	}
	else {
		assert(false);
	}
	return nullptr;
}
