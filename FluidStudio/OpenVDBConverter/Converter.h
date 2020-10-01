#pragma once

#include <openvdb/openvdb.h>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace OpenVDB {

class Converter {
public:
    static openvdb::Vec3R toVDB(const Crystal::Math::Vector3dd& p)
    {
        return openvdb::Vec3R(p.x, p.y, p.z);
    }

    static std::vector<openvdb::Vec3R> toVDB(const std::vector<Crystal::Math::Vector3dd>& positions)
    {
        std::vector<openvdb::Vec3R> dest(positions.size());
        for (int i = 0; i < positions.size(); ++i) {
            dest[i] = toVDB(positions[i]);
        }
        return dest;
    }
};

    }
}