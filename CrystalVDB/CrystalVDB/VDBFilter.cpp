#include "VDBFilter.h"

#include "VDBVolumeImpl.h"

#include "openvdb/openvdb.h"
#include "openvdb/tools/Filter.h"

using namespace Crystal::VDB;

void VDBFilter::median(int width, int iteration)
{
	auto grid = this->src->getImpl()->getPtr();
	openvdb::tools::Filter<openvdb::FloatGrid> filter(*grid);
	filter.median(width, iteration);
}