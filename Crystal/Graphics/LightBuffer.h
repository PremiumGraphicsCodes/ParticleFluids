#pragma once

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "PointLight.h"

namespace Crystal {
	namespace Graphics {

class LightBuffer
{
public:
	LightBuffer() {};

	void clear() {
		position.clear();
		diffuse.clear();
		specular.clear();
		ambient.clear();
	}

	void add(const PointLight& light) {
		this->position.add(light.getPosition());
		this->diffuse.add(light.getDiffuse());
		this->specular.add(light.getSpecular());
		this->ambient.add(light.getAmbient());
	}

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer3d<float> getDiffuse() const { return diffuse; }

	Graphics::Buffer3d<float> getSpecular() const { return specular; }

	Graphics::Buffer3d<float> getAmbient() const { return ambient; }

	void merge(const LightBuffer& rhs) {
		this->position.merge(rhs.position);
		this->diffuse.merge(rhs.diffuse);
		this->specular.merge(rhs.specular);
		this->ambient.merge(rhs.ambient);
	}

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer3d<float> diffuse;
	Graphics::Buffer3d<float> specular;
	Graphics::Buffer3d<float> ambient;
};

	}
}
