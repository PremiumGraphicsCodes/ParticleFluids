#include "PhysicsSolverExportCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"
#include "Crystal/IO/PCDBinaryFileWriter.h"

namespace {
	PublicLabel CommandNameLabel = "PhysicsSolverExportCommand";
	PublicLabel FluidIdsLabel = "FluidIds";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel DoExportMicroLabel = "DoExportMicro";
}

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverExportCommand::getName()
{
	return ::CommandNameLabel;
}

PhysicsSolverExportCommand::Args::Args() :
	fluidIds(::FluidIdsLabel, {}),
	filePath(::FilePathLabel, ""),
	doExportMicro(::DoExportMicroLabel, false)
{
	add(&fluidIds);
	add(&filePath);
	add(&doExportMicro);
}

PhysicsSolverExportCommand::Results::Results()
{
}

PhysicsSolverExportCommand::PhysicsSolverExportCommand() :
	ICommand(&args, &results)
{}

bool PhysicsSolverExportCommand::execute(World* world)
{
	PCDFile pcd;
	for (const auto id : args.fluidIds.getValue()) {
		auto fluid = world->getScenes()->findSceneById<MVPFluidScene*>(id);
		if (fluid == nullptr) {
			return false;
		}
		const auto macroParticles = fluid->getParticles();
		if (args.doExportMicro.getValue()) {
			/*
			for (const auto mp : macroParticles) {
				const auto micros = mp->getMassParticles();
				for (const auto micro : micros) {
					pcd.data.positions.push_back(micro->getPosition());
				}
			}
			*/
		}
		else {
			for (const auto mp : macroParticles) {
				pcd.data.positions.push_back(mp->getPosition());
			}
		}
	}
	pcd.header.width = pcd.data.positions.size();
	pcd.header.points = pcd.data.positions.size();

	PCDBinaryFileWriter writer;
	const auto isOk = writer.write(args.filePath.getValue(), pcd);

	return isOk;
}
