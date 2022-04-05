#include "VDBCommandFactory.h"

#include "VDBInitCommand.h"
#include "VDBFileWriteCommand.h"
#include "VDBFileReadCommand.h"
#include "VDBOBJFileReadCommand.h"
#include "VDBOBJFileWriteCommand.h"
#include "VDBSTLFileReadCommand.h"
#include "VDBSTLFileWriteCommand.h"
#include "VDBPLYFileReadCommand.h"
#include "VDBPLYFileWriteCommand.h"
#include "VDBPCDFileReadCommand.h"
#include "VDBPCDFileWriteCommand.h"
#include "VDBSceneCreateCommand.h"
#include "VDBPSToVolumeCommand.h"
#include "VDBMeshToVolumeCommand.h"
#include "VDBVolumeToMeshCommand.h"
#include "VDBVolumeToPSCommand.h"
#include "VDBFilterCommand.h"
#include "ToVDBVolumeCommand.h"

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
	else if (name == VDBOBJFileReadCommand::getName()) {
		return std::make_unique<VDBOBJFileReadCommand>();
	}
	else if (name == VDBOBJFileWriteCommand::getName()) {
		return std::make_unique<VDBOBJFileWriteCommand>();
	}
	else if (name == VDBSTLFileReadCommand::getName()) {
		return std::make_unique<VDBSTLFileReadCommand>();
	}
	else if (name == VDBSTLFileWriteCommand::getName()) {
		return std::make_unique<VDBSTLFileWriteCommand>();
	}
	else if (name == VDBPLYFileReadCommand::getName()) {
		return std::make_unique<VDBPLYFileReadCommand>();
	}
	else if (name == VDBPLYFileWriteCommand::getName()) {
		return std::make_unique<VDBPLYFileWriteCommand>();
	}
	else if (name == VDBPCDFileReadCommand::getName()) {
		return std::make_unique<VDBPCDFileReadCommand>();
	}
	else if (name == VDBPCDFileWriteCommand::getName()) {
		return std::make_unique<VDBPCDFileWriteCommand>();
	}
	else if (name == VDBSceneCreateCommand::getName()) {
		return std::make_unique<VDBSceneCreateCommand>();
	}
	else if (name == VDBPSToVolumeCommand::getName()) {
		return std::make_unique<VDBPSToVolumeCommand>();
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
	else if (name == VDBVolumeToPSCommand::getName()) {
		return std::make_unique<VDBVolumeToPSCommand>();
	}
	else if (name == ToVDBVolumeCommand::getName()) {
		return std::make_unique<ToVDBVolumeCommand>();
	}
	else if (name == VDBFilterCommand::getName()) {
		return std::make_unique<VDBFilterCommand>();
	}
	else {
		assert(false);
	}
	return nullptr;
}
