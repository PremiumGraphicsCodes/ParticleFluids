#pragma once

#include "IObject.h"
#include "../Shape/ParticleSystem.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace UI {

class LightObject : public IObject
{
public:
	LightObject(const int id, const std::string& name, Graphics::PointLight* light) :
		IObject(id,name),
		light(light)
	{}

	~LightObject() {};

	//Shape::ParticleSystem<ParticleAttr>* getShape() const { return shape; }

	Graphics::PointLight* getLight() const { return light; }

private:
	Graphics::PointLight* light;
};

	}
}