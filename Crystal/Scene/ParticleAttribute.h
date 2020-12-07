#pragma once

#include "../Graphics/ColorRGBA.h"
#include "../Shape/IParticle.h"

namespace Crystal {
	namespace Scene {

struct ParticleAttribute : Shape::IParticleAttribute
{
	Graphics::ColorRGBAf color;
	float size;
};

	}
}