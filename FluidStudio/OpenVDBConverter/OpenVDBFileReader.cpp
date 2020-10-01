#include "OpenVDBFileReader.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

namespace {
    openvdb::io::File file("");
}

OpenVDBFileReader::~OpenVDBFileReader()
{
    close();
}

bool OpenVDBFileReader::open(const std::string& filename)
{
    file = openvdb::io::File(filename);
    const auto isOk = file.open();
    return isOk;
}

void OpenVDBFileReader::close()
{
    file.close();
}

std::vector<std::string> OpenVDBFileReader::getPointGridNames() const
{
    std::vector<std::string> names;
    auto metas = file.readAllGridMetadata();
    for (auto iter = metas->begin(); iter != metas->end(); ++iter) {
        const auto isPoint = (*iter)->isType<openvdb::points::PointDataGrid>();
        if (isPoint) {
            //std::cout << (*iter)->getName() << std::endl;
            names.push_back((*iter)->getName());
        }
    }
    return names;
}

std::vector<Vector3dd> OpenVDBFileReader::readPositions(const std::string& pointName)
{
    auto baseGrid = file.readGrid(pointName);

    auto grid = openvdb::gridPtrCast<openvdb::points::PointDataGrid>(baseGrid);
    auto count = openvdb::points::pointCount(grid->tree());
    //std::cout << "PointCount=" << count << std::endl;

    std::vector<openvdb::Vec3R> v_positions;
    std::vector<openvdb::Index32> v_indices;

    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
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
            v_positions.push_back(worldPosition);
            auto index = *indexIter;
            v_indices.push_back(index);
        }
    }

    std::vector<Vector3dd> positions(v_positions.size());
    for (const auto i : v_indices) {
        positions[i] = Converter::fromVDB(v_positions[i]);
    }

    return std::move(positions);
}
