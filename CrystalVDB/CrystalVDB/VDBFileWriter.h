#pragma once

#include <string>
#include <vector>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {
        class VDBParticleSystem;
        class VDBVolumeScene;

class VDBFileWriter
{
public:
    ~VDBFileWriter();

    bool open(const std::string& filePath);

    void close();

    void writePoints(const std::string& name, const std::vector<Math::Vector3dd>& positions) const;

    void writeVolumes(const std::vector<VDBVolumeScene*>& volumes) const;

private:
};

    }
}