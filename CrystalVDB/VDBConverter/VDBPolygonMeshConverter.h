#pragma once

#include "VDBPolygonMesh.h"
#include "VDBVolumeScene.h"

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace VDB {

class VDBPolygonMeshConverter
{
public:
	void toVolume(const VDBPolygonMesh& mesh, VDBVolumeScene* volume);

	std::unique_ptr<Shape::PolygonMesh> fromVDB(const VDBPolygonMesh& src);

private:
};

	}
}