#include "MeshToVoxelCommand.h"

#include "PublicLabels/MeshToVoxelLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;

MeshToVoxelCommand::MeshToVoxelCommand() :
	ICommand(&args, &results)
{}

MeshToVoxelCommand::Args::Args() :
	meshId(::PolygonMeshIdLabel, -1),
	voxelId(::VoxelIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0)
{
	add(&meshId);
	add(&voxelId);
	add(&divideLength);
}

MeshToVoxelCommand::Results::Results()
{
}

std::string MeshToVoxelCommand::getName()
{
	return ::CommandNameLabel;
}

bool MeshToVoxelCommand::execute(World* scene)
{
	return false;
}