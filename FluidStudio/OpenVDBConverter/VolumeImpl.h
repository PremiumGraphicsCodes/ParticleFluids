#pragma once

#include "openvdb/openvdb.h"

namespace Crystal {
	namespace OpenVDB {

class VolumeImpl
{
public:
	VolumeImpl() {}

	/*
	explicit VolumeImpl(openvdb::FloatGrid::Ptr ptr) :
		ptr(std::move(ptr))
	{
	}
	*/

	~VolumeImpl() {}

	openvdb::FloatGrid::Ptr getPtr() { return ptr; }

	void setPtr(openvdb::FloatGrid::Ptr ptr) { this->ptr = ptr; }

private:
	openvdb::FloatGrid::Ptr ptr;
};
	}
}