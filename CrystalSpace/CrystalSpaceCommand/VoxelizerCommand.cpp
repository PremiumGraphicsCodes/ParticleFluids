#include "VoxelizerCommand.h"

#include "PublicLabels/VoxelizerLabels.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../CrystalSpace/Voxelizer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Space;
using namespace Crystal::Scene;

VoxelizerCommand::VoxelizerCommand() :
	ICommand(&args, &results)
{}

VoxelizerCommand::Args::Args() :
	meshId(::MeshIdLabel, -1),
	psId(::PSIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0)
{
	add(&meshId);
	add(&psId);
	add(&divideLength);
}

VoxelizerCommand::Results::Results()
{
}

std::string VoxelizerCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelizerCommand::execute(World* scene)
{
	auto pmScene = scene->getScenes()->findSceneById<PolygonMeshScene*>(args.meshId.getValue());
	if (pmScene == nullptr) {
		return false;
	}
	auto psScene = scene->getScenes()->findSceneById<ParticleSystemScene*>(args.psId.getValue());
	if (psScene == nullptr) {
		return false;
	}
	Voxelizer converter;
	converter.voxelize(*pmScene->getShape(), args.divideLength.getValue());
	psScene->getShape()->clear();
	const auto points = converter.getPoints();
	ParticleAttribute attr;
	attr.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	attr.size = 10.0;
	for (const auto& p : points) {
		psScene->getShape()->add(p, attr);
	}
	return true;
}