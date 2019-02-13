#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

class IParticle
{
public:
	~IParticle()
	{}

	virtual Math::Vector3dd getPosition() const = 0;

	virtual void move(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;

	virtual void transform(const Math::Matrix4dd& m) = 0;
};

template<typename Attr>
class Particle : public IParticle
{
public:
	Particle(const Math::Vector3dd& position, const Attr& attr) :
		position(position),
		attribute(attr)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	void move(const Math::Vector3dd& v) override { this->position += v; }

	void transform(const Math::Matrix3dd& m) override { position = m * position; }

	void transform(const Math::Matrix4dd& m) override { position = m * glm::vec4(position, 1.0); }

	Attr getAttribute() const { return attribute; }

private:
	Math::Vector3dd position;
	Attr attribute;
};

	}
}