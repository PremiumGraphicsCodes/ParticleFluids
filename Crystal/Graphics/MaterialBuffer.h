#pragma once

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "Material.h"

namespace Crystal {
	namespace Graphics {

class MaterialBuffer
{
public:
	MaterialBuffer() {};

	void add(const Graphics::Material& m) {
		this->ambient.add(m.ambient);
		this->diffuse.add(m.diffuse);
		this->specular.add(m.specular);
		this->shininess.add(m.shininess);
	}

	Graphics::Buffer3d<float> getAmbient() const { return ambient; }

	Graphics::Buffer3d<float> getDiffuse() const { return diffuse; }

	Graphics::Buffer3d<float> getSpecular() const { return specular; }

	Graphics::Buffer1d<float> getShininess() const { return shininess; }

private:
	Graphics::Buffer3d<float> ambient;
	Graphics::Buffer3d<float> diffuse;
	Graphics::Buffer3d<float> specular;
	Graphics::Buffer1d<float> shininess;
};

	}
}