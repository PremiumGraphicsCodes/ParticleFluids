#include "CommandFactory.h"

#include "MockCommand.h"
#include "FileImportCommand.h"
#include "ParticleSystemAddCommand.h"

using namespace Crystal::Command;

std::unique_ptr<ICommand> CommandFactory::create(const std::string& name)
{
	if (name == "Mock") {
		return std::make_unique<MockCommand>();
	}
	else if (name == "FileImport") {
		return std::make_unique<FileImportCommand>();		
	}
	else if (name == "ParticleSystemAdd") {
		return std::make_unique<ParticleSystemAddCommand>();
	}
	assert(false);
	return nullptr;
}