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

using namespace Crystal::VDB;

int main()
{
    Crystal::Scene::World world;

    {
        VDBInitCommand command;
        command.execute(&world);
    }

    int psId = -1;
    {
        VDBPCDFileReadCommand::Args args;
        args.filePath.setValue("C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt//macro1.pcd");
        VDBPCDFileReadCommand command(args);
        command.execute(&world);
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

    double radius = 1.0;
    double voxelSize = 0.5;
    {
        VDBPSToVolumeCommand::Args args;
        args.particleSystemId.setValue(psId);
        args.vdbVolumeId.setValue(volumeId);
        args.radius.setValue(radius);
        args.voxelSize.setValue(voxelSize);
        VDBPSToVolumeCommand command(args);
        std::cout << "Converting PS to Volume" << std::endl;
        const auto isOk = command.execute(&world);
        if (!isOk) {
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

    int meshId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBMesh");
        VDBSceneCreateCommand command(args);
        std::cout << "Creating Empty Mesh" << std::endl;
        const auto isOk = command.execute(&world);
        if (!isOk) {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
        meshId = std::any_cast<int>(command.getResults().newId.value);
    }
    /*
    {
        VDBVolumeToMeshCommand::Args args;
        args.vdbMeshId
    }
    */


    std::cout << "Hello World!\n";
}

