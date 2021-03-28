#include "VDBVolumeImpl.h"

using namespace Crystal::VDB;

void VDBVolumeImpl::setScale(const double scale)
{
	this->getPtr()->setTransform(openvdb::math::Transform::createLinearTransform(scale));
}

void VDBVolumeImpl::setScale(const double sx, const double sy, const double sz)
{
	openvdb::Mat4R m = openvdb::Mat4R::identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	this->getPtr()->setTransform(openvdb::math::Transform::createLinearTransform(m));
}
