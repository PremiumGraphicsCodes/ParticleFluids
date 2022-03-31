#include "VDBSmoothingCommand.h"

#include "../CrystalVDB/VDBFilter.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSmoothing";
	PublicLabel VDBVolumeIdLabel = "VDBVolumeId";
	PublicLabel WidthLabel = "Width";
	PublicLabel IterationLabel = "Iteration";
	PublicLabel FilterTypeLabel = "FilterType";
	PublicLabel FilterType_MedianLabel = "Median";
	PublicLabel FilterType_MeanLabel = "Mean";
	PublicLabel FilterType_GaussianLabel = "Gaussian";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSmoothingCommand::Args::Args() :
	vdbVolumeId(::VDBVolumeIdLabel, -1),
	width(::WidthLabel, 1),
	iteration(::IterationLabel, 1),
	filterType(::FilterTypeLabel, ::FilterType_MedianLabel)
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

	const auto type = args.filterType.getValue();

	const auto width = args.width.getValue();
	const auto iter = args.iteration.getValue();

	VDBFilter filter;
	filter.setSource(volume);
	if (type == ::FilterType_MedianLabel) {
		filter.median(width, iter);
	}
	else if (type == ::FilterType_GaussianLabel) {
		filter.gaussian(width, iter);
	}
	else if (type == ::FilterType_MeanLabel) {
		filter.mean(width, iter);
	}

	return true;
}
