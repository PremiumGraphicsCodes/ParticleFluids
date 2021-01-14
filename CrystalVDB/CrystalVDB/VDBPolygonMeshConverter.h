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
	void toVolume(const VDBPolygonMeshScene& mesh, VDBVolumeScene* volume);

	void fromVDB(const VDBPolygonMeshScene& src, Shape::PolygonMesh* dest);

private:
};

	}
}