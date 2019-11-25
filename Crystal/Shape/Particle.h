#pragma once

#include "IPoint.h"

namespace Crystal {
	namespace Shape {

template<typename Attr>
class Particle : public IPoint
{
public:
	Particle()
	{}

	Particle(const Math::Vector3dd& position, const Attr& attr) :
		position(position),
		attribute(attr)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	void move(const Math::Vector3dd& v) override { this->position += v; }

	void transform(const Math::Matrix3dd& m) override { position = m * position; }

	void transform(const Math::Matrix4dd& m) override { position = m * glm::vec4(position, 1.0); }

	Attr getAttribute() const { return attribute; }

	void setAttribute(Attr attr) { this->attribute = attr; }

	Particle<Attr>* clone() const {
		return new Particle(position, attribute);
	}

private:
	Math::Vector3dd position;
	Attr attribute;
};

	}
}