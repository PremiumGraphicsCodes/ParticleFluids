#pragma once

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace VDB {
		class VDBPolygonMeshScene;
		class VDBVolumeScene;

class VDBPolygonMeshConverter
{
public:
	void fromVDB(const VDBPolygonMeshScene& src, Shape::PolygonMesh* dest);

private:
};

	}
}