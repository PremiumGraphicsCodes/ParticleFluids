#include "VDBCommandFactory.h"

#include "VDBInitCommand.h"
#include "VDBFileWriteCommand.h"
#include "VDBFileReadCommand.h"
#include "VDBOBJFileWriteCommand.h"
#include "VDBSceneCreateCommand.h"
#include "VDBMeshToVolumeCommand.h"
#include "VDBVolumeToMeshCommand.h"
#include "VDBVolumeToPSCommand.h"

#include "VDBSceneFileReadCommand.h"
#include "VDBSceneFileWriteCommand.h"
#include "VDBSceneFileImportCommand.h"
#include "VDBSceneFileExportCommand.h"
#include "VDBSceneFilterCommand.h"
#include "VDBSceneCompositeCommand.h"
#include "VDBSceneResamplingCommand.h"
#include "VDBScenePSToVolumeCommand.h"

using namespace Crystal::Command;
using namespace Crystal::VDB;

std::unique_ptr<ICommand> VDBCommandFactory::createCommand(const std::string& name) const
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
	else if (name == VDBOBJFileWriteCommand::getName()) {
		return std::make_unique<VDBOBJFileWriteCommand>();
	}
	else if (name == VDBSceneCreateCommand::getName()) {
		return std::make_unique<VDBSceneCreateCommand>();
	}
	else if (name == VDBVolumeToPSCommand::getName()) {
		return std::make_unique<VDBVolumeToPSCommand>();
	}
	else if (name == VDBMeshToVolumeCommand::getName()) {
		return std::make_unique<VDBMeshToVolumeCommand>();
	}
	else if (name == VDBVolumeToMeshCommand::getName()) {
		return std::make_unique<VDBVolumeToMeshCommand>();
	}
	else if (name == VDBSceneFileReadCommand::getName()) {
		return std::make_unique<VDBSceneFileReadCommand>();
	}
	else if (name == VDBSceneFileWriteCommand::getName()) {
		return std::make_unique<VDBSceneFileWriteCommand>();
	}
	else if (name == VDBSceneFileImportCommand::getName()) {
		return std::make_unique<VDBSceneFileImportCommand>();
	}
	else if (name == VDBSceneFileExportCommand::getName()) {
		return std::make_unique<VDBSceneFileExportCommand>();
	}
	else if (name == VDBSceneFilterCommand::getName()) {
		return std::make_unique<VDBSceneFilterCommand>();
	}
	else if (name == VDBSceneCompositeCommand::getName()) {
		return std::make_unique<VDBSceneCompositeCommand>();
	}
	else if (name == VDBSceneResamplingCommand::getName()) {
		return std::make_unique<VDBSceneResamplingCommand>();
	}
	else if (name == VDBScenePSToVolumeCommand::getName()) {
		return std::make_unique<VDBScenePSToVolumeCommand>();
	}
	else {
		assert(false);
	}
	return nullptr;
}
