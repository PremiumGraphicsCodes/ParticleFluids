#include "SpaceCommandFactory.h"

#include "SparseVolumeSceneCreateCommand.h"
#include "SparseVolumeNodeSetCommand.h"

using namespace Crystal::Command;
using namespace Crystal::Space;

std::unique_ptr<ICommand> SpaceCommandFactory::create(const std::string& name)
{
	if (name == SparseVolumeSceneCreateCommand::getName()) {
		return std::make_unique<SparseVolumeSceneCreateCommand>();
	}
	else if (name == SparseVolumeNodeSetCommand::getName()) {
		return std::make_unique<SparseVolumeNodeSetCommand>();
	}
	assert(false);
	return nullptr;
}
