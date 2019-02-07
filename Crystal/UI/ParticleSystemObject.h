#pragma once

#include "IObject.h"
#include "../Shape/ParticleSystem.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace UI {

struct ParticleAttr
{
	Graphics::ColorRGBAf color;
	float size;
};

class ParticleSystemObject : public IObject
{
public:
	ParticleSystemObject(const int id, const std::string& name, Shape::ParticleSystem<ParticleAttr>* shape) :
		IObject(id, name),
		shape(shape)
	{}

	~ParticleSystemObject() {};

	Shape::ParticleSystem<ParticleAttr>* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

private:
	Shape::ParticleSystem<ParticleAttr>* shape;
};

	}
}