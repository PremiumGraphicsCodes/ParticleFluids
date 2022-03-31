#include "VDBTransformCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeScene.h"
#include "CrystalVDB/CrystalVDB/VDBTransform.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBTransform";
	PublicLabel SourceVolumeIdLabel = "SourceVolumeId";
	PublicLabel TargetVolumeIdLabel = "TargetVolumeId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBTransformCommand::Args::Args() :
	sourceVolumeId(::SourceVolumeIdLabel, -1),
	targetVolumeId(::TargetVolumeIdLabel, -1)
{
	add(&sourceVolumeId);
	add(&targetVolumeId);
}

VDBTransformCommand::Results::Results()
{
}

VDBTransformCommand::VDBTransformCommand() :
	ICommand(&args, &results)
{}

VDBTransformCommand::VDBTransformCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBTransformCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBTransformCommand::execute(World* world)
{
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.sourceVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}

	auto target = world->getScenes()->findSceneById<VDBVolumeScene* >(args.targetVolumeId.getValue());
	if (target == nullptr) {
		return false;
	}

	VDBTransform transform;
	transform.transformGeometry();

	return true;
}