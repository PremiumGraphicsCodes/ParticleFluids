#pragma once

#include <string>
#include <vector>

namespace Crystal {
    namespace VDBTool {

struct CommandLineOptions
{
    std::string inputPsFilePath = "C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt//macro1.pcd";
    double particleRadius = 1.0;
    double voxelSize = 0.5;
    std::string outputMeshFilePath = "mesh.obj";

    void parse(const std::vector<std::string>& strs) {
        for (int i = 0; i < strs.size(); ++i) {
            std::string str = strs[i];
            if (str == "-i") {
                i++;
                this->inputPsFilePath = strs[i];
            }
            else if (str == "-o") {
                i++;
                this->outputMeshFilePath = strs[i];
            }
            else if (str == "-r") {
                i++;
                this->particleRadius = std::stod(strs[i]);
            }
            else if (str == "-v") {
                i++;
                this->voxelSize = std::stod(strs[i]);
            }
        }
    }
};

    }
}