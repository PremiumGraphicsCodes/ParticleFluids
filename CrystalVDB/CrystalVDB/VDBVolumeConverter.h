#pragma once

namespace Crystal {
	namespace Scene {
		class IParticleSystemScene;
	}
	namespace VDB {
		class VDBVolumeScene;
		class VDBPolygonMeshScene;
		//class VDBParticleSystemScene;

class VDBVolumeConverter
{
public:
	void toMesh(const VDBVolumeScene& volume, VDBPolygonMeshScene* mesh);

	void toParticleSystem(const VDBVolumeScene& volume, IParticleSystemScene* ps) const;

private:
};

	}
}