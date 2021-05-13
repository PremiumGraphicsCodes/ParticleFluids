#include "VoxelNodeSetCommand.h"

//#include "../../Crystal/Scene/ParticleAttribute.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "PublicLabels/VoxelNodeSetLabels.h"

#include "../CrystalSpace/VoxelScene.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

VoxelNodeSetCommand::Args::Args() :
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

VoxelNodeSetCommand::Results::Results()// :
//	newId(::NewIdLabel, -1)
{
	//	add(&newId);
}

std::string VoxelNodeSetCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelNodeSetCommand::execute(World* world)
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
		std::array<int, 3> index{ indicesx[i], indicesy[i], indicesz[i] };
		auto n = shape->createNode(index);
		n->setValue(values[i]);
	}

	return true;
}
