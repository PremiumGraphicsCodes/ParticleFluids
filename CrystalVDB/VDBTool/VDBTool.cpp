// VDBTool.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBPCDFileReadCommand.h"
#include "CrystalVDB/VDBCommand/ToVDBVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneCreateCommand.h"
#include "CrystalVDB/VDBCommand/VDBPSToVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileWriteCommand.h"

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

    double radius = 0.1;
    {
        VDBPSToVolumeCommand::Args args;
        args.particleSystemId.setValue(psId);
        args.vdbVolumeId.setValue(volumeId);
        args.radius.setValue(radius);
        VDBPSToVolumeCommand command(args);
        command.execute(&world);
    }

    {
        VDBFileWriteCommand::Args args;
        args.filePath.setValue("volume.vdb");
        args.vdbVolumeIds.setValue({ volumeId });
        VDBFileWriteCommand command(args);
        command.execute(&world);
    }


    std::cout << "Hello World!\n";
}

