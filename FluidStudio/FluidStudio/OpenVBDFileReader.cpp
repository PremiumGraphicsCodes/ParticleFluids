#include "OpenVBDFileReader.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::OpenVDB;

bool OpenVDBFileReader::read(const std::string& filename)
{
    openvdb::io::File newFile(filename);

    const auto isOk = newFile.open();
    if (!isOk) {
        return false;
    }
    auto baseGrid = newFile.readGrid("Points");
    newFile.close();

    auto grid = openvdb::gridPtrCast<openvdb::points::PointDataGrid>(baseGrid);
    auto count = openvdb::points::pointCount(grid->tree());
    std::cout << "PointCount=" << count << std::endl;
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        const auto& array = leafIter->constAttributeArray("P");

        // Create a read-only AttributeHandle. Position always uses Vec3f.
        openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
        // Iterate over the point indices in the leaf.
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
            const auto xyz = indexIter.getCoord().asVec3d();
            openvdb::Vec3f worldPosition =
                grid->transform().indexToWorld(voxelPosition + xyz);
            this->positions.push_back(worldPosition);
            auto index = *indexIter;
            indices.push_back(index);
        }
    }
}
