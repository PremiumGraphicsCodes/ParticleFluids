#pragma once

#include "IScene.h"
#include "../Shape/ParticleSystem.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Model {

class LightObject : public IScene
{
public:
	LightObject(const int id, const std::string& name, Graphics::PointLight* light) :
		IScene(id,name),
		light(light)
	{}

	~LightObject() {};

	Graphics::PointLight* getLight() const { return light; }

	void move(const Math::Vector3dd& v) override { light->move(v); }

	void transform(const Math::Matrix3dd& m) { light->transform(m); }

	void transform(const Math::Matrix4dd& m) { light->transform(m); }

	bool isNull() const { return light == nullptr; }

	ObjectType getType() const override { return ObjectType::LightObject; }

private:
	Graphics::PointLight* light;
};

	}
}