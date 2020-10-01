#include "OpenVDBAdapter.h"

#include <openvdb/openvdb.h>

using namespace Crystal::OpenVDB;

void OpenVDBAdapter::init()
{
	openvdb::initialize();
}
