#pragma once

#include <string>
#include <vector>
#include <openvdb/openvdb.h>
#include <openvdb/points/PointConversion.h>

namespace Crystal {
    namespace OpenVDB {

class FSPSFileReader
{
public:
    void read(const std::string& filename);

    std::vector<openvdb::Vec3R> getPositions() const { return positions; }

private:
    std::vector<openvdb::Vec3R> positions;
};

    }
}