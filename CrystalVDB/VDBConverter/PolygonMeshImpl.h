#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
    namespace VDB {

class PolygonMeshImpl
{
public:
    std::vector<openvdb::Vec3s> points;
    std::vector<openvdb::Vec4I> quads;
    std::vector<openvdb::Vec3I> triangles;
    std::vector<openvdb::Vec3s> normals;

    void clear()
    {
        points.clear();
        quads.clear();
        triangles.clear();
        normals.clear();
    }

    void updateNormals();
};

    }
}