#include "VDBVolumeImpl.h"

using namespace Crystal::VDB;

void VDBVolumeImpl::setScale(const double scale)
{
	this->getPtr()->setTransform(openvdb::math::Transform::createLinearTransform(scale));
}