#include "OpenVDBCommandFactory.h"

#include "OpenVDBFileWriteCommand.h"
#include "OpenVDBFileReadCommand.h"

using namespace Crystal::Command;
using namespace Crystal::OpenVDB;

std::unique_ptr<ICommand> OpenVDBCommandFactory::createCommand(const std::string& name)
{
	if (name == OpenVDBFileWriteCommand::getName()) {
		return std::make_unique<OpenVDBFileWriteCommand>();
	}
	else if (name == OpenVDBFileReadCommand::getName()) {
		return std::make_unique<OpenVDBFileReadCommand>();
	}
	else {
		assert(false);
	}
}
