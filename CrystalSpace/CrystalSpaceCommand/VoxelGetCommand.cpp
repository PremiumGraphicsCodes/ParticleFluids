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
	resX(::ResolutionXLabel, 0),
	resY(::ResolutionYLabel, 0),
	resZ(::ResolutionZLabel, 0),
	values(::ValuesLabel, {})
{
	add(&resX);
	add(&resY);
	add(&resZ);
	add(&values);
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

	const auto res = shape->getResolutions();
	std::vector<bool> values;
	for (int i = 0; i < res[0]; ++i) {
		for (int j = 0; j < res[1]; ++j) {
			for (int k = 0; k < res[2]; ++k) {
				values.push_back(shape->getValue(i, j, k));
			}
		}
	}

	results.resX.setValue(res[0]);
	results.resY.setValue(res[1]);
	results.resZ.setValue(res[2]);
	results.values.setValue(values);

	return true;
}
