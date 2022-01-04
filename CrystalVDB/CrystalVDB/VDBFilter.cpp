#include "openvdb/openvdb.h"
#include "openvdb/tools/Filter.h"

namespace {
	void median(int width, int iteration)
	{
		const openvdb::Coord dim(40);
		const openvdb::FloatGrid::ConstPtr referenceGrid;
		const openvdb::FloatTree& filteredTree = referenceGrid->tree();

		openvdb::Coord xyz;
		openvdb::FloatGrid::Ptr filteredGrid = referenceGrid->deepCopy();

		openvdb::tools::Filter<openvdb::FloatGrid> filter(*filteredGrid);
		filter.median(width, iteration);
	}
}