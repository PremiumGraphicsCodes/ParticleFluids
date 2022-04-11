#include "FluidVolumeExportCommand.h"

#include "../CrystalPhysics/FluidVolumeScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "Crystal/IO/PLYFileWriter.h"

namespace {
	PublicLabel CommandNameLabel = "FluidVolumeExportCommand";
	PublicLabel VolumeIdLabel = "VolumeId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidVolumeExportCommand::getName()
{
	return ::CommandNameLabel;
}

FluidVolumeExportCommand::Args::Args() :
	volumeId(::VolumeIdLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&volumeId);
	add(&filePath);
}

FluidVolumeExportCommand::Results::Results()
{
}

FluidVolumeExportCommand::FluidVolumeExportCommand() :
	ICommand(&args, &results)
{}

bool FluidVolumeExportCommand::execute(World* world)
{
	PLYFile file;
	file.properties.push_back(PLYProperty("x", PLYType::INT));
	file.properties.push_back(PLYProperty("y", PLYType::INT));
	file.properties.push_back(PLYProperty("z", PLYType::INT));
	file.properties.push_back(PLYProperty("density", PLYType::FLOAT));
	auto volume = world->getScenes()->findSceneById<FluidVolumeScene*>(args.volumeId.getValue());
	if (volume == nullptr) {
		return false;
	}
	const auto nodes = volume->getShape()->getNodes();
	for (const auto n : nodes) {
		const auto i = n->getIndex();
		PLYPoint p;
		p.values.push_back(i[0]);
		p.values.push_back(i[1]);
		p.values.push_back(i[2]);
		p.values.push_back(n->getValue());
		file.vertices.push_back(p);
	}

	PLYFileWriter writer;
	const auto isOk = writer.writeASCII(args.filePath.getValue(), file);
	return isOk;
}
