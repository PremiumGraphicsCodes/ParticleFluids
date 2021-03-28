#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeImpl
{
public:
	VDBVolumeImpl()
	{
	}

	explicit VDBVolumeImpl(openvdb::FloatGrid::Ptr ptr) :
		ptr(ptr)
	{}

	~VDBVolumeImpl() {}

	openvdb::FloatGrid::Ptr getPtr() { return ptr; }

	void setPtr(openvdb::FloatGrid::Ptr ptr) { this->ptr = ptr; }

	void setScale(const double scale);

	void setScale(const double sx, const double sy, const double sz);

private:
	openvdb::FloatGrid::Ptr ptr;
};
	}
}