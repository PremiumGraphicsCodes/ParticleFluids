#include "MVPSurfaceConstructionCommand.h"

#include "Crystal/Shape/IParticleSystem.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
//using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

namespace {
	PublicLabel CommandNameLabel = "MPVSurfaceConstructionCommand";
	PublicLabel VolumeParticleSystemIdLabel = "VolumeParticleSystemId";
	PublicLabel MassParticleSystemIdLabel = "MassParticleSystemId";
	PublicLabel TriangleMeshIdLabel = "TriangleMeshId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel ThresholdLabel = "Threshold";
}

std::string MVPSurfaceConstructionCommand::getName()
{
	return ::CommandNameLabel;
}

MVPSurfaceConstructionCommand::Args::Args() :
	volumeParticleSystemId(::VolumeParticleSystemIdLabel, -1),
	massParticleSystemId(::MassParticleSystemIdLabel, -1),
	triangleMeshId(::TriangleMeshIdLabel, -1),
	particleRadius(::ParticleRadiusLabel, 1.0),
	threshold(::ThresholdLabel, 1.0f)
{
	add(&volumeParticleSystemId);
	add(&massParticleSystemId);
	add(&triangleMeshId);
	add(&particleRadius);
	add(&threshold);
}

MVPSurfaceConstructionCommand::Results::Results()// :
//	newId(::NewIdLabel, 0)
{
	//	add(&newId);
}

MVPSurfaceConstructionCommand::MVPSurfaceConstructionCommand() :
	ICommand(&args, &results)
{}

bool MVPSurfaceConstructionCommand::execute(World* world)
{
	auto ps = world->getScenes()->findSceneById<IParticleSystemScene*>(args.volumeParticleSystemId.getValue());
	if (ps == nullptr) {
		return false;
	}
	auto tm = world->getScenes()->findSceneById<TriangleMeshScene*>(args.triangleMeshId.getValue());
	if (tm == nullptr) {
		return false;
	}
}