#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VDBPolygonMeshConverter
{
public:
	std::unique_ptr<VDBVolume> toVolume(const VDBPolygonMesh& mesh);

	std::unique_ptr<Shape::PolygonMesh> fromVDB(const VDBPolygonMesh& src);

private:
};

	}
}