#include "PolygonMeshImpl.h"

using namespace Crystal::VDB;

namespace {
	openvdb::Vec3s getNormal(const std::vector<openvdb::Vec3s>& positions, const int p0, const int p1, const int p2)
	{
		const auto& v0 = positions[p0];
		const auto& v1 = positions[p1];
		const auto& v2 = positions[p2];
		auto v21 = openvdb::Vec3s(v2 - v1);
		v21.normalize();
		auto v01 = openvdb::Vec3d(v0 - v1);
		v01.normalize();
		const auto normal = v21.cross(v01);
		return normal;
	}
}


void PolygonMeshImpl::updateNormals()
{
	this->normals.clear();
	for (const auto& t : triangles) {
		this->normals.push_back( getNormal(points, t[0], t[1], t[2]) );
	}
	for (const auto& q : quads) {
		this->normals.push_back(getNormal(points, q[0], q[1], q[2]));
	}
}
