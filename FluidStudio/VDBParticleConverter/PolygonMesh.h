#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
    namespace OpenVDB {

class PolygonMesh
{
public:
    std::vector<openvdb::Vec3s> points;
    std::vector<openvdb::Vec4I> quads;
    std::vector<openvdb::Vec3I> triangles;

    void clear()
    {
        points.clear();
        quads.clear();
        triangles.clear();
    }
};

    }
}