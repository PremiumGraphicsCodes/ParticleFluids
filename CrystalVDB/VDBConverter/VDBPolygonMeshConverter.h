#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolume.h"

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace VDB {

class VDBPolygonMeshConverter
{
public:
	void toVolume(const VDBPolygonMesh& mesh, VDBVolume* volume);

	std::unique_ptr<Shape::PolygonMesh> fromVDB(const VDBPolygonMesh& src);

private:
};

	}
}