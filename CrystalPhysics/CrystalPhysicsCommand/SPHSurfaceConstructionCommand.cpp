#include "SPHSurfaceConstructionCommand.h"

//#include "../CrystalPhysics/KFFluidScene.h"
#include "CrystalScene/Scene/IParticleSystemScene.h"
#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include "../../CrystalPhysics/CrystalPhysics/SurfaceConstruction/SPHSurfaceBuilder.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "SPHSurfaceConstructionCommand";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel SparseVolumeIdLabel = "SparseVolumeId";
	PublicLabel EffectLengthLabel = "EffectLength";
	PublicLabel CellLengthLabel = "CellLength";
}


using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string SPHSurfaceConstructionCommand::getName()
{
	return ::CommandNameLabel;
}

SPHSurfaceConstructionCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	sparseVolumeId(::SparseVolumeIdLabel, -1),
	effectLength(::EffectLengthLabel, 1.0),
	cellLength(::CellLengthLabel, 0.5)
{
	add(&particleSystemId);
	add(&sparseVolumeId);
	add(&effectLength);
	add(&cellLength);
}

SPHSurfaceConstructionCommand::Results::Results()// :
//	newId(::NewIdLabel, 0)
{
//	add(&newId);
}

SPHSurfaceConstructionCommand::SPHSurfaceConstructionCommand() :
	ICommand(&args, &results)
{}

bool SPHSurfaceConstructionCommand::execute(World* world)
{
	auto ps = world->getScenes()->findSceneById<IParticleSystemScene*>(args.particleSystemId.getValue());
	if (ps == nullptr) {
		return false;
	}
	auto sp = world->getScenes()->findSceneById<SparseVolumeScene*>(args.sparseVolumeId.getValue());
	if (sp == nullptr) {
		return false;
	}

	auto positions = ps->getPositions();

	SPHSurfaceBuilder builder;
	builder.buildAnisotoropic(positions, args.effectLength.getValue(), args.cellLength.getValue());
	auto shape = builder.getVolume();
	sp->resetShape(std::move(shape));
	//sp->
	//results.newId.setValue(fluidScene->getId());
	return true;
}