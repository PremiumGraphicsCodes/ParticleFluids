#include <iostream>
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBSceneCreateCommand.h"
//#include "CrystalVDB/VDBCommand/VDBSTLFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBMeshToVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBVolumeToPSCommand.h"

using namespace Crystal::VDB;

struct CommandLineOptions
{
    std::string inputMeshFilePath = "C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt//macro1.pcd";
    std::string outputPsFilePath = "mesh.stl";
    double divideLength = 1.0;

    void parse(const std::vector<std::string>& strs) {
        for (int i = 0; i < strs.size(); ++i) {
            std::string str = strs[i];
            if (str == "-i") {
                i++;
                this->inputMeshFilePath = strs[i];
            }
            else if (str == "-o") {
                i++;
                this->outputPsFilePath = strs[i];
            }
            else if (str == "-l") {
                i++;
                this->divideLength = std::stod(strs[i]);
            }
        }
    }
};

int main()
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

    int volumeId = -1;
    {
        VDBSceneCreateCommand::Args args;
        args.sceneType.setValue("VDBVolume");
        VDBSceneCreateCommand command(args);
        command.execute(&world);
        volumeId = std::any_cast<int>(command.getResults().newId.value);
    }

    int meshId = -1;
    std::cout << "Converting Mesh to Volume...";
    {
        VDBMeshToVolumeCommand::Args args;
        args.divideLength.setValue(1.0);
        args.vdbMeshId.setValue(meshId);
        args.vdbVolumeId.setValue(volumeId);
        VDBMeshToVolumeCommand command(args);
        const auto isOk = command.execute(&world);
        if (isOk) {
            std::cout << "Succeeded" << std::endl;
        }
        else {
            std::cout << "Failed" << std::endl;
            std::exit(1);
        }
    }

    int particleSystemId = -1;
    {
        VDBVolumeToPSCommand::Args args;
        args.vdbParticleSystemId.setValue( particleSystemId );
        args.vdbVolumeId.setValue( volumeId );
        VDBVolumeToPSCommand command(args);
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
