#include "SpaceCommandFactory.h"

#include "SparseVolumeSceneCreateCommand.h"
#include "SparseVolumeNodeSetCommand.h"
#include "VoxelSceneCreateCommand.h"
#include "VoxelNodeSetCommand.h"
#include "MeshToPSCommand.h"
#include "MeshToVoxelCommand.h"
#include "VoxelToPSCommand.h"

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
	else if (name == VoxelSceneCreateCommand::getName()) {
		return std::make_unique<VoxelSceneCreateCommand>();
	}
	else if (name == VoxelNodeSetCommand::getName()) {
		return std::make_unique<VoxelNodeSetCommand>();
	}
	else if (name == MeshToPSCommand::getName()) {
		return std::make_unique<MeshToPSCommand>();
	}
	else if (name == MeshToVoxelCommand::getName()) {
		return std::make_unique<MeshToVoxelCommand>();
	}
	else if (name == VoxelToPSCommand::getName()) {
		return std::make_unique<VoxelToPSCommand>();
	}
	assert(false);
	return nullptr;
}