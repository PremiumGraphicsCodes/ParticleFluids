#pragma once

#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Graphics/SpotLight.h"
#include "../../CrystalSpace/CrystalAlgo/CompactSpaceHash3d.h"

namespace Crystal {
	namespace Photon {
		class PhotonCloudScene;

class PhotonTracer
{
public:
	void add(Shape::IParticle* particle);

	void build(const double searchRadius, const size_t tableSize);

	void generatePhoton(const Graphics::SpotLight& light);

	void trance(PhotonCloudScene* photonCloud, const float length);

private:
	std::vector<Shape::IParticle*> particles;
	Crystal::Search::CompactSpaceHash3d spaceHash;
};
	}
}