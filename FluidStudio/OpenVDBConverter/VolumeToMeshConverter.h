#pragma once

#include "PolygonMeshImpl.h"

namespace Crystal {
	namespace OpenVDB {

class VolumeToMeshConverter
{
public:
	PolygonMeshImpl toMesh(openvdb::FloatGrid grid);

private:
	PolygonMeshImpl mesh;
};

	}
}