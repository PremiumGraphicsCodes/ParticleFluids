#pragma once

namespace Crystal {
	namespace Space {
		template<typename T>
		class SparseVolume;
	}
	namespace VDB {
		class VDBVolumeScene;
		class VDBPolygonMeshScene;
		class VDBParticleSystemScene;

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolumeScene& volume, VDBPolygonMeshScene* mesh, const double threshold, const double adaptivity);

	void toParticleSystem(const VDBVolumeScene& volume, VDBParticleSystemScene* ps) const;

	void fromSparseVolume(const Crystal::Space::SparseVolume<float>& sp, VDBVolumeScene* volume) const;
private:
};

	}
}