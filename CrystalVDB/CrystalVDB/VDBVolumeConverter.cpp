#include "VDBVolumeConverter.h"

#include <openvdb/openvdb.h>

#include <openvdb/points/PointSample.h>
#include <openvdb/tools/LevelSetUtil.h>


#include "openvdb/tools/VolumeToMesh.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"
#include "VDBPolygonMeshScene.h"
#include "VDBPolygonMeshImpl.h"
#include "VDBParticleSystemImpl.h"
#include "VDBParticleSystemScene.h"
#include "Converter.h"

#include "CrystalSpace/CrystalSpace/SparseVolume.h"

using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

void VDBVolumeConverter::toMesh(const VDBVolumeScene& volume, VDBPolygonMeshScene* mesh, const double threshold, const double adaptivity)
{   
    auto impl = mesh->getImpl();
    impl->clear();
    auto grid = volume.getImpl()->getPtr();
    std::vector<openvdb::Vec3I> triangles;
    std::vector<openvdb::Vec4I> quads;
    openvdb::tools::volumeToMesh(*grid, impl->points, triangles, quads, threshold, adaptivity);
    for (const auto& t : triangles) {
        Crystal::VDB::VDBPolygonMeshImpl::TriangleFace face;
        face.indices = t;
        impl->triangles.push_back(face);
    }
    for (const auto& q : quads) {
        Crystal::VDB::VDBPolygonMeshImpl::QuadFace face;
        face.indices = q;
        impl->quads.push_back(face);
    }
    impl->updateNormals();
}

void VDBVolumeConverter::toParticleSystem(const VDBVolumeScene& volume, VDBParticleSystemScene* ps) const
{
    auto impl = volume.getImpl();
    auto grid = impl->getPtr();
    auto transform = grid->transform();
    for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
        auto coord = transform.indexToWorld(iter.getCoord());
        ps->getImpl()->add(coord, 1.0);
    }
}

void VDBVolumeConverter::fromSparseVolume(const SparseVolume<double>& sp, VDBVolumeScene* volume) const
{
    const auto length = sp.getCellLength();
    Crystal::Math::Matrix4dd matrix
    (
        length[0], 0.0, 0.0, 0.0,
        0.0, length[1], 0.0, 0.0,
        0.0, 0.0, length[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    volume->getImpl()->setTransformMatrix(matrix);
    auto& accesor = volume->getImpl()->getPtr()->getAccessor();
    const auto bb = sp.getBoundingBox();
    const auto nodes = sp.getNodes();
    for (auto n : nodes) {
        const auto ix = n->getIndex();
        openvdb::math::Coord c(ix[0], ix[1], ix[2]);
        accesor.setValue(c, n->getValue());
    }
    //Converter::toVDB()
    //volume->getImpl()->getPtr()->
    //volume->setValue()
}
