#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
	namespace OpenVDB {

class VolumeImpl
{
public:
	VolumeImpl() {}

	VolumeImpl(openvdb::FloatGrid::Ptr ptr) :
		ptr(std::move(ptr))
	{
	}

	~VolumeImpl() {}

	openvdb::FloatGrid::Ptr getPtr() { return ptr; }

private:
	openvdb::FloatGrid::Ptr ptr;
};
	}
}