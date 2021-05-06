#include "MeshToPSCommand.h"

#include "PublicLabels/MeshToPSLabels.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../CrystalSpace/MeshToParticleAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

MeshToPSCommand::Args::Args() :
	polygonMeshId(::PolygonMeshIdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0)
{
	add(&polygonMeshId);
	add(&particleSystemId);
	add(&divideLength);
}

MeshToPSCommand::Results::Results()// :
//	newId(::NewIdLabel, -1)
{
	//	add(&newId);
}

std::string MeshToPSCommand::getName()
{
	return ::CommandNameLabel;
}

bool MeshToPSCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<PolygonMeshScene*>(args.polygonMeshId.getValue());
	if (scene == nullptr) {
		return false;
	}

	/*
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
	*/

	return true;
}
