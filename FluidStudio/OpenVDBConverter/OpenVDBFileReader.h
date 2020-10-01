#pragma once

#include <string>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace OpenVDB {

class OpenVDBFileReader
{
public:
    bool read(const std::string& filename);

    std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
    std::vector<Math::Vector3dd> positions;
};

    }
}