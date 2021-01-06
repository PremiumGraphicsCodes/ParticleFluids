#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
    namespace VDB {

class PolygonMeshImpl
{
public:
    struct TriangleFace
    {
        openvdb::Vec3I indices;
        openvdb::Vec3s normal;
    };

    struct QuadFace
    {
        openvdb::Vec4I indices;
        openvdb::Vec3s normal;
    };

    std::vector<openvdb::Vec3s> points;
    std::vector<TriangleFace> triangles;
    std::vector<QuadFace> quads;

    std::vector<openvdb::Vec3I> getTriangles() const {
        std::vector<openvdb::Vec3I> results;
        for (const auto& q : triangles) {
            results.push_back(q.indices);
        }
        return results;
    }

    std::vector<openvdb::Vec4I> getQuads() const {
        std::vector<openvdb::Vec4I> results;
        for (const auto& q : quads) {
            results.push_back(q.indices);
        }
        return results;
    }

    void clear()
    {
        points.clear();
        triangles.clear();
        quads.clear();
    }

    void updateNormals();
};

    }
}