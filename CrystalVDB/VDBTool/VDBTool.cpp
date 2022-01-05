// VDBTool.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBPCDFileReadCommand.h"
#include "CrystalVDB/VDBCommand/ToVDBVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneCreateCommand.h"
#include "CrystalVDB/VDBCommand/VDBPSToVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileWriteCommand.h"
#include "CrystalVDB/VDBCommand/VDBVolumeToMeshCommand.h"
#include "CrystalVDB/VDBCommand/VDBOBJFileWriteCommand.h"

using namespace Crystal::VDB;

struct CommandLineOptions
{
    std::string inputPsFilePath = "C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt//macro1.pcd";
    double particleRadius = 1.0;
    double voxelSize = 0.5;
    std::string outputMeshFilePath = "mesh.obj";

    void parse(int argc, char* argv[]) {
        for (int i = 0; i < argc; ++i) {
            std::string str(argv[i]);
            if (str == "-i") {
                i++;
                this->inputPsFilePath = argv[i];
            }
            else if (str == "-o") {
                i++;
                this->outputMeshFilePath = argv[i];
            }
            else if (str == "-r") {
                i++;
                std::string s(argv[i]);
                this->particleRadius = std::stod(s);
            }
        }
    }
};

int main(int argc, char* argv[])
{
    CommandLineOptions options;
    options.parse(argc, argv);

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
    std::cout << "Reading PCD File...";
    {
        VDBPCDFileReadCommand::Args args;
        args.filePath.setValue(options.inputPsFilePath);
        VDBPCDFileReadCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
        psId = std::any_cast<int>( command.getResult("VDBPSId") );
    }

    int volumeId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBVolume");
        VDBSceneCreateCommand command(args);
        command.execute(&world);
        volumeId = std::any_cast<int>(command.getResults().newId.value);
    }

    std::cout << "Converting PS to Volume...";
    {
        VDBPSToVolumeCommand::Args args;
        args.particleSystemId.setValue(psId);
        args.vdbVolumeId.setValue(volumeId);
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

    /*
    {
        VDBFileWriteCommand::Args args;
        args.filePath.setValue("volume.vdb");
        args.vdbVolumeIds.setValue({ volumeId });
        VDBFileWriteCommand command(args);
        command.execute(&world);
    }
    */

    std::cout << "Creating Empty Mesh...";
    int meshId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBMesh");
        VDBSceneCreateCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
        meshId = std::any_cast<int>(command.getResults().newId.value);
    }

    std::cout << "Converting Volume to Mesh...";
    {
        VDBVolumeToMeshCommand::Args args;
        args.vdbVolumeId.setValue(volumeId);
        args.vdbMeshId.setValue(meshId);
        VDBVolumeToMeshCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    std::cout << "Writing OBJ ...";
    {
        VDBOBJFileWriteCommand::Args args;
        args.filePath.setValue(options.outputMeshFilePath);
        args.vdbMeshId.setValue(meshId);
        VDBOBJFileWriteCommand command(args);
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