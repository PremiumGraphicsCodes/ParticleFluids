#include "VDBTransformCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeScene.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeImpl.h"

//#include "openvdb/tools/GridTransformer.h"

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

	/*
	auto sourceGrid = volume->getImpl()->getPtr();
	auto targetGrid = target->getImpl()->getPtr();

	const openvdb::math::Transform
		& sourceXform = sourceGrid->transform(),
		& targetXform = targetGrid->transform();

	// Compute a source grid to target grid transform.
	// (For this example, we assume that both grids' transforms are linear,
	// so that they can be represented as 4 x 4 matrices.)
	openvdb::Mat4R xform =
		sourceXform.baseMap()->getAffineMap()->getMat4() *
		targetXform.baseMap()->getAffineMap()->getMat4().inverse();

	// Create the transformer.
	openvdb::tools::GridTransformer transformer(xform);
	// Resample using nearest-neighbor interpolation.
	transformer.transformGrid<openvdb::tools::PointSampler, openvdb::FloatGrid>(
		*sourceGrid, *targetGrid);

	/*
	// Resample using trilinear interpolation.
	transformer.transformGrid<openvdb::tools::BoxSampler, openvdb::FloatGrid>(
		*sourceGrid, *targetGrid);
	// Resample using triquadratic interpolation.
	transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
		*sourceGrid, *targetGrid);
		*/
	// Prune the target tree for optimal sparsity.
	//targetGrid->tree().prune();
	*/

	return true;
}
