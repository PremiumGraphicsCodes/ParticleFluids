#pragma once

#include <openvdb/openvdb.h>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace OpenVDB {

class Converter {
public:
    static openvdb::Vec3R toVDB(const Crystal::Math::Vector3dd& p);

    static std::vector<openvdb::Vec3R> toVDB(const std::vector<Crystal::Math::Vector3dd>& positions);

    static Crystal::Math::Vector3df fromVDB(const openvdb::Vec3f& p);

    static Crystal::Math::Vector3dd fromVDB(const openvdb::Vec3R& p);

    static std::vector<Crystal::Math::Vector3dd> fromVDB(const std::vector<openvdb::Vec3R>& positions);

    static openvdb::Vec3I toVDB(const std::array<int, 3>& indices);

    static std::array<unsigned int, 3> fromVDB(const openvdb::Vec3I& src);

    static openvdb::Vec4I toVDB(const std::array<int, 4>& indices);

};

    }
}