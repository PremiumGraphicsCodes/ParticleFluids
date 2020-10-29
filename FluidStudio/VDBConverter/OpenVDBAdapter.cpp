#include "OpenVDBAdapter.h"

#include <openvdb/openvdb.h>

using namespace Crystal::VDB;

void OpenVDBAdapter::init()
{
	openvdb::initialize();
}
