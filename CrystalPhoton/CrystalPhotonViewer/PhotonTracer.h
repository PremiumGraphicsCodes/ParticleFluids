#pragma once

#include "../../Crystal/Graphics/PointLight.h"
#include "Photon.h"

namespace Crystal {
	namespace Photon {

class PhotonTracer
{
public:
	void add(Shape::IParticle* particle);

	void add(Graphics::PointLight* light);

	void trance();
private:
};
	}
}