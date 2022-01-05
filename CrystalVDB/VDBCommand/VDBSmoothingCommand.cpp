#include "VDBSmoothingCommand.h"

#include "../CrystalVDB/VDBFilter.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSmoothing";
	PublicLabel VDBVolumeIdLabel = "VDBVolumeId";
	PublicLabel WidthLabel = "Width";
	PublicLabel IterationLabel = "Iteration";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSmoothingCommand::Args::Args() :
	vdbVolumeId(::VDBVolumeIdLabel, -1),
	width(::WidthLabel, 1),
	iteration(::IterationLabel, 1)
{
	add(&vdbVolumeId);
	add(&width);
	add(&iteration);
}

VDBSmoothingCommand::Results::Results()
{
}

VDBSmoothingCommand::VDBSmoothingCommand() :
	ICommand(&args, &results)
{}

VDBSmoothingCommand::VDBSmoothingCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSmoothingCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSmoothingCommand::execute(World* world)
{
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbVolumeId.getValue());
	if (volume == nullptr) {
		return false;
	}

	VDBFilter filter;
	filter.setSource(volume);
	filter.median(args.width.getValue(), args.iteration.getValue());

	return true;
}
