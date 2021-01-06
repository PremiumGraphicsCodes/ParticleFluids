#pragma once

#include "VDBPolygonMeshScene.h"
#include "VDBVolumeScene.h"

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace VDB {

class VDBPolygonMeshConverter
{
public:
	void toVolume(const VDBPolygonMeshScene& mesh, VDBVolumeScene* volume);

	std::unique_ptr<Shape::PolygonMesh> fromVDB(const VDBPolygonMeshScene& src);

private:
};

	}
}