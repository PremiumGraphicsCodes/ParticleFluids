#pragma once

namespace Crystal {
	namespace Space {
		class SparseVolumeScene;
	}
	namespace VDB {
		class VDBVolumeScene;
		class VDBPolygonMeshScene;
		class VDBParticleSystemScene;

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolumeScene& volume, VDBPolygonMeshScene* mesh);

	void toParticleSystem(const VDBVolumeScene& volume, VDBParticleSystemScene* ps) const;

	void toVDB(const Space::SparseVolumeScene& sv, VDBVolumeScene* vdb);

private:
};

	}
}