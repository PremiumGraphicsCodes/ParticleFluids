#include "OpenVDBFileWriter.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

//openvdb::Vec3R

namespace {
    openvdb::Vec3R toVDB(const Vector3dd& p)
    {
        return openvdb::Vec3R( p.x, p.y, p.z );
    }

    std::vector<openvdb::Vec3R> toVDB(const std::vector<Vector3dd>& positions)
    {
        std::vector<openvdb::Vec3R> dest(positions.size());
        for (int i = 0; i < positions.size(); ++i) {
            dest[i] = toVDB(positions[i]);
        }
        return dest;
    }
}

void OpenVDBFileWriter::write(const std::string& filename)
{
    std::vector<openvdb::Vec3R> ps = toVDB(positions);
    openvdb::points::PointAttributeVector<openvdb::Vec3R> positionsWrapper(ps);

    int pointsPerVoxel = 8;
    float voxelSize = openvdb::points::computeVoxelSize(positionsWrapper, pointsPerVoxel);

    auto transform = openvdb::math::Transform::createLinearTransform(voxelSize);
    auto grid = openvdb::points::createPointDataGrid
        <
        openvdb::points::NullCodec,
        openvdb::points::PointDataGrid
        >
        (ps, *transform);

    grid->setName(name);

    openvdb::io::File file(filename);
    file.write({ grid });
    file.close();
}
