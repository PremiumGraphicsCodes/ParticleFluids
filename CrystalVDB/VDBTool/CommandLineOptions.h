#pragma once

#include <string>
#include <vector>

namespace Crystal {
    namespace VDBTool {

struct CommandLineOptions
{
    std::string inputPsFilePath = "C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt//macro1.pcd";
    std::string outputVolumeFilePath = "volume.vdb";
    double particleRadius = 1.0;
    double voxelSize = 0.5;
    double threshold = 0.0;
    double meshAdaptivity = 0.0;
    int smoothingWidth = 1;
    int smoothingIteration = 1;

    void parse(const std::vector<std::string>& strs) {
        for (int i = 0; i < strs.size(); ++i) {
            std::string str = strs[i];
            if (str == "-i") {
                i++;
                this->inputPsFilePath = strs[i];
            }
            else if (str == "-o") {
                i++;
                this->outputVolumeFilePath = strs[i];
            }
            else if (str == "-r") {
                i++;
                this->particleRadius = std::stod(strs[i]);
            }
            else if (str == "-v") {
                i++;
                this->voxelSize = std::stod(strs[i]);
            }
            else if (str == "-t") {
                i++;
                this->threshold = std::stod(strs[i]);
            }
            else if (str == "-a") {
                i++;
                this->meshAdaptivity = std::stod(strs[i]);
            }
            else if (str == "-sw") {
                i++;
                this->smoothingWidth = std::stoi(strs[i]);
            }
            else if (str == "-si") {
                i++;
                this->smoothingIteration = std::stoi(strs[i]);
            }
        }
    }
};

    }
}