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

#include "../../Crystal/Math/Matrix4d.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

using namespace Crystal::Space;
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

void VDBVolumeConverter::toVDB(const SparseVolumeScene& sv, VDBVolumeScene* vdb)
{
    auto impl = vdb->getImpl();
    auto sdf = openvdb::createLevelSet<openvdb::FloatGrid>();
    sdf->setName("density");
    impl->setPtr(sdf);
//    auto grid = impl->getPtr();
 //   grid->
    auto nodes = sv.getShape()->getNodes();
    for (const auto& n : nodes) {
        const auto index = n.first;
        const auto value = n.second->getValue();
        openvdb::math::Coord coord(index[0], index[1], index[2]);
        impl->getPtr()->getAccessor().setValue(coord, value);
    }
    const auto bb = sv.getBoundingBox();
    const auto scale = bb.getLength();
    const auto translate = bb.getMin();

    const auto originalBB = vdb->getBoundingBox();
    const auto originalScale = originalBB.getLength();

    const auto sx = scale.x / originalScale.x;
    const auto sy = scale.y / originalScale.y;
    const auto sz = scale.z / originalScale.z;

    impl->setScale(sx, sy, sz);
    impl->setTranslate(translate);
    /*
    Crystal::Math::Matrix4dd matrix(
        scale.x, 0.0, 0.0, 0.0,
        0.0, scale.y, 0.0, 0.0,
        0.0, 0.0, scale.z, 0.0,
        -0.5, -0.5, -0.5, 1.0
    );
    impl->setTransformMatrix(matrix);
    */
}
