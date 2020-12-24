#include "MeshToVolumeConverter.h"

#include "PolygonMeshImpl.h"
#include "VolumeImpl.h"

#include <openvdb/tools/MeshToVolume.h>

using namespace Crystal::VDB;

std::unique_ptr<VDBVolume> MeshToVolumeConverter::toVolume(const VDBPolygonMesh& mesh)
{
	openvdb::math::Transform::Ptr xform = openvdb::math::Transform::createLinearTransform();
	openvdb::tools::QuadAndTriangleDataAdapter<openvdb::Vec3s, openvdb::Vec4I> m(mesh.getImpl()->points, mesh.getImpl()->quads);
	auto result = openvdb::tools::meshToVolume<openvdb::FloatGrid>(m, *xform);
	auto impl = new VolumeImpl(result);
	return std::make_unique<VDBVolume>(impl);
}
