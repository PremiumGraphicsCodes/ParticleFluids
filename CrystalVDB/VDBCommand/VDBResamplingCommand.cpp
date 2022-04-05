#include "VDBResamplingCommand.h"

#include "../CrystalVDB/VDBResampler.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBResampling";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel SamplingTypeLabel = "SamplingType";
	PublicLabel SamplingType_PointLabel = "Point";
	PublicLabel SamplingType_BoxLabel = "Box";
	PublicLabel SamplingType_QuadricLabel = "Quadric";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBResamplingCommand::Args::Args() :
	volumeId(::VolumeIdLabel, -1),
	samplingType(::SamplingTypeLabel, ::SamplingType_PointLabel)
{
	add(&volumeId);
	add(&samplingType);
}

VDBResamplingCommand::Results::Results()
{
}

VDBResamplingCommand::VDBResamplingCommand() :
	ICommand(&args, &results)
{}

VDBResamplingCommand::VDBResamplingCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBResamplingCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBResamplingCommand::execute(World* world)
{
	auto volume = world->getScenes()->findSceneById<VDBVolumeScene*>(args.volumeId.getValue());
	if (volume == nullptr) {
		return false;
	}

	VDBResampler resampler;
	resampler.setSource(volume);

	const auto samplingType = args.samplingType.getValue();
	if (samplingType == ::SamplingType_PointLabel) {
		resampler.point();
	}
	else if (samplingType == ::SamplingType_BoxLabel) {
		resampler.box();
	}
	else if (samplingType == ::SamplingType_QuadricLabel) {
		resampler.quadratic();
	}
	else {
		assert(false);
		return false;
	}

	return true;
}
