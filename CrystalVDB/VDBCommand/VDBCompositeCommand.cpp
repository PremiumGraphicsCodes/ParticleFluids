#include "VDBCompositeCommand.h"

using namespace Crystal::Command;

#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBComposite.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBComposite";
	PublicLabel VolumeId1Label = "VolumeId1";
	PublicLabel VolumeId2Label = "VolumeId2";
	PublicLabel CompositeTypeLabel = "CompositeType";
	PublicLabel CompositeType_Union = "Union";
	PublicLabel CompositeType_Difference = "Difference";
	PublicLabel CompositeType_Intersection = "Intersection";
}

//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBCompositeCommand::Args::Args() :
	volumeId1(::VolumeId1Label, -1),
	volumeId2(::VolumeId2Label, 1),
	compositeType(::CompositeTypeLabel, ::CompositeType_Union)
{
	add(&volumeId1);
	add(&volumeId2);
	add(&compositeType);
}

VDBCompositeCommand::Results::Results()
{
}

VDBCompositeCommand::VDBCompositeCommand() :
	ICommand(&args, &results)
{}

VDBCompositeCommand::VDBCompositeCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBCompositeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBCompositeCommand::execute(World* world)
{
	auto volume1 = world->getScenes()->findSceneById<VDBVolumeScene*>(args.volumeId1.getValue());
	if (volume1 == nullptr) {
		return false;
	}

	auto volume2 = world->getScenes()->findSceneById<VDBVolumeScene*>(args.volumeId2.getValue());
	if (volume2 == nullptr) {
		return false;
	}

	VDBComposite composite;
	const auto type = args.compositeType.getValue();
	if (type == ::CompositeType_Union) {

	}
	else if (type == ::CompositeType_Difference) {
		composite.csgDifference(volume1, volume2);
	}
	else if (type == "") {
		composite.csgIntersection(volume1, volume2);
	}
	else {
		assert(false);
		return false;
	}

	return true;
}
