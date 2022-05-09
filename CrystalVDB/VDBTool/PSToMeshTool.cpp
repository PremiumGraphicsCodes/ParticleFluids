#include "PSToMeshTool.h"

#include <iostream>
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
//#include "CrystalVDB/VDBCommand/VDBPCDFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBPLYFileReadCommand.h"
#include "CrystalVDB/VDBCommand/ToVDBVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneCreateCommand.h"
#include "CrystalVDB/VDBCommand/VDBPSToVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileWriteCommand.h"
#include "CrystalVDB/VDBCommand/VDBVolumeToMeshCommand.h"
#include "CrystalVDB/VDBCommand/VDBSTLFileWriteCommand.h"
//#include "CrystalVDB/VDBCommand/VDBSmoothingCommand.h"

using namespace Crystal::VDB;
using namespace Crystal::VDBTool;

void PSToMeshTool::execute(const CommandLineOptions& options)
{
    Crystal::Scene::World world;

    std::cout << "Initializing VDB...";
    {
        VDBInitCommand command;
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    int psId = -1;
    {
        VDBSceneCreateCommand::Args scArgs;
        scArgs.sceneType.setValue("VDBPoints");
        VDBSceneCreateCommand scCommand(scArgs);
        scCommand.execute(&world);
        psId = std::any_cast<int>(scCommand.getResult("NewId"));
    }

    std::cout << "Reading PLY File...";
    {
        VDBPLYFileReadCommand::Args args;
        args.vdbSceneId.setValue(psId);
        args.filePath.setValue(options.inputPsFilePath);
        VDBPLYFileReadCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    int volumeId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBVolume");
        args.name.setValue("density");
        VDBSceneCreateCommand command(args);
        command.execute(&world);
        volumeId = std::any_cast<int>(command.getResults().newId.value);
    }

    int temperatureId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBVolume");
        args.name.setValue("temperature");
        VDBSceneCreateCommand command(args);
        command.execute(&world);
        temperatureId = std::any_cast<int>(command.getResults().newId.value);
    }

    std::cout << "Converting PS to Volume...";
    {
        VDBPSToVolumeCommand::Args args;
        args.doUseSph.setValue(true);
        args.particleSystemId.setValue(psId);
        args.vdbVolumeId.setValue(volumeId);
        args.temperatureVolumeId.setValue(temperatureId);
        args.radius.setValue(options.particleRadius);
        args.voxelSize.setValue(options.voxelSize);
        VDBPSToVolumeCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    std::cout << "Writing Volume...";
    {
        VDBFileWriteCommand::Args args;
        args.filePath.setValue(options.outputVolumeFilePath);
        args.vdbVolumeIds.setValue({ volumeId, temperatureId });
        VDBFileWriteCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }
}