#include "VoxelSetCommand.h"

//#include "../../Crystal/Scene/ParticleAttribute.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/VoxelSetLabels.h"

#include "../CrystalSpace/VoxelScene.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

VoxelSetCommand::Args::Args() :
	voxelId(::VoxelIdLabel, -1),
	indicesX(::IndicesXLabel, { 0 }),
	indicesY(::IndicesYLabel, { 0 }),
	indicesZ(::IndicesZLabel, { 0 }),
	values(::ValuesLabel, {})
{
	add(&voxelId);
	add(&indicesX);
	add(&indicesY);
	add(&indicesZ);
	add(&values);
}

VoxelSetCommand::Results::Results()// :
//	newId(::NewIdLabel, -1)
{
	//	add(&newId);
}

std::string VoxelSetCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (scene == nullptr) {
		return false;
	}

	auto shape = scene->getShape();

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

	return true;
}
