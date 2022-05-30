#pragma once

namespace Crystal {
	namespace VDB {
		class VDBPolygonMeshScene;
		class VDBVolumeScene;

class VDBMeshToVolumeConverter
{
public:
	static VDBVolumeScene* toVolume(const VDBPolygonMeshScene& mesh, const double divideLength);

private:
};

	}
}