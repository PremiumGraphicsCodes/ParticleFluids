#include "VDBVolumeConverter.h"

#include <openvdb/openvdb.h>

#include <openvdb/points/PointSample.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"
#include "VDBPolygonMeshScene.h"
#include "VDBPolygonMeshImpl.h"
#include "VDBParticleSystemImpl.h"
#include "VDBParticleSystemScene.h"

using namespace Crystal::Scene;
using namespace Crystal::VDB;

void VDBVolumeConverter::toMesh(const VDBVolumeScene& volume, VDBPolygonMeshScene* mesh)
{   
    auto impl = mesh->getImpl();
    impl->clear();
    auto grid = volume.getImpl()->getPtr();
    std::vector<openvdb::Vec4I> quads;
    openvdb::tools::volumeToMesh(*grid, impl->points, quads);
    for (const auto& q : quads) {
        Crystal::VDB::VDBPolygonMeshImpl::QuadFace face;
        face.indices = q;
        impl->quads.push_back(face);
    }
    impl->updateNormals();
}

void VDBVolumeConverter::toParticleSystem(const VDBVolumeScene& volume, IParticleSystemScene* ps) const
{
    auto impl = volume.getImpl();
    auto grid = impl->getPtr();
    auto transform = grid->transform();
    for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
        auto coord = transform.indexToWorld(iter.getCoord());
        ps->add
//        ps->getImpl()->add(coord, 1.0);
    }
}
