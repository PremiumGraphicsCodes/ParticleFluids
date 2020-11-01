#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
	namespace VDB {

class VolumeImpl
{
public:
	VolumeImpl()
	{
	}

	explicit VolumeImpl(openvdb::FloatGrid::Ptr ptr) :
		ptr(ptr)
	{}

	~VolumeImpl() {}

	openvdb::FloatGrid::Ptr getPtr() { return ptr; }

	void setPtr(openvdb::FloatGrid::Ptr ptr) { this->ptr = ptr; }

private:
	openvdb::FloatGrid::Ptr ptr;
};
	}
}