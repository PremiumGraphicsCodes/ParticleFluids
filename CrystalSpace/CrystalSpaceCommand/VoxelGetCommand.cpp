#include "VoxelGetCommand.h"

#include "PublicLabels/VoxelGetLabels.h"

#include "../CrystalSpace/VoxelScene.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

VoxelGetCommand::Args::Args() :
	voxelId(::VoxelIdLabel, -1)
{
	add(&voxelId);
}

VoxelGetCommand::Results::Results() :
	indicesX(::IndicesXLabel, {}),
	indicesY(::IndicesYLabel, {}),
	indicesZ(::IndicesZLabel, {}),
	values(::ValuesLabel, {})
//	newId(::NewIdLabel, -1)
{
	//	add(&newId);
}

std::string VoxelGetCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelGetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (scene == nullptr) {
		return false;
	}

	auto shape = scene->getShape();

	/*
	const auto indicesx = args.indicesX.getValue();
	const auto indicesy = args.indicesY.getValue();
	const auto indicesz = args.indicesZ.getValue();
	const auto values = args.values.getValue();

	assert(indicesx.size() == indicesy.size());
	assert(indicesy.size() == indicesz.size());
	assert(indicesz.size() == values.size());

	for (int i = 0; i < indicesx.size(); ++i) {
		shape->setValue(indicesx[i], indicesy[i], indicesz[i], values[i]);
	}
	*/

	return true;
}
