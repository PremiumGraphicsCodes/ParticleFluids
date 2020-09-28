#pragma once

#include "PolygonMesh.h"

namespace Crystal {
	namespace OpenVDB {

class VolumeToMeshConverter
{
public:
	PolygonMesh toMesh(openvdb::FloatGrid grid);

private:
	PolygonMesh mesh;

};
	}
}