#pragma once

#include "../../Crystal/Graphics/SpotLight.h"
#include "Photon.h"

namespace Crystal {
	namespace Photon {

class PhotonTracer
{
public:
	void add(Shape::IParticle* particle);

	void add(Graphics::SpotLight* light);

	void trance();

private:
	std::vector<Graphics::SpotLight*> lights;
	std::vector<Shape::IParticle*> particles;
};
	}
}