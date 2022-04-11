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
	/*
	PLYFile file;
	file.properties.push_back(PLYProperty("ix", PLYType::INT));
	file.properties.push_back(PLYProperty("iy", PLYType::INT));
	file.properties.push_back(PLYProperty("iz", PLYType::INT));
	file.properties.push_back(PLYProperty("density", PLYType::FLOAT))
	for (const auto id : args.fluidIds.getValue()) {
		auto fluid = world->getScenes()->findSceneById<IMVPFluidScene*>(id);
		if (fluid == nullptr) {
			return false;
		}
		const auto macroParticles = fluid->getParticles();
		if (args.doExportMicro.getValue()) {
			for (const auto mp : macroParticles) {
				const auto micros = mp->getMassParticles();
				for (const auto micro : micros) {
					const auto pp = micro->position;
					PLYPoint p;
					p.values.push_back(pp.x);
					p.values.push_back(pp.y);
					p.values.push_back(pp.z);
					file.vertices.push_back(p);
				}
			}
		}
		else {
			for (const auto mp : macroParticles) {
				const auto pp = mp->getPositionf();
				PLYPoint p;
				p.values.push_back(pp.x);
				p.values.push_back(pp.y);
				p.values.push_back(pp.z);

				file.vertices.push_back(p);
			}
		}
	}

	PLYFileWriter writer;
	const auto isOk = writer.writeBinary(args.filePath.getValue(), file);
	return isOk;
	*/
	return false;
}
