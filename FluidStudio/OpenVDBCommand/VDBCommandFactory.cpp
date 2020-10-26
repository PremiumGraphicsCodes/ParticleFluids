#include "VDBCommandFactory.h"

#include "VDBInitCommand.h"
#include "VDBFileWriteCommand.h"
#include "VDBFileReadCommand.h"

using namespace Crystal::Command;
using namespace Crystal::OpenVDB;

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
	else {
		assert(false);
	}
}
