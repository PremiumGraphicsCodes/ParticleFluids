#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

template<typename Attr>
class Particle
{
public:
	Particle(const Math::Vector3dd& position, const Attr& attr) :
		position(position),
		attribute(attr)
	{}

	Math::Vector3dd getPosition() const { return position; }

	void move(const Math::Vector3dd& v) { this->position += v; }

	void transform(const Math::Matrix3dd& m) { position = m * position; }

	void transform(const Math::Matrix4dd& m) { position = m * glm::vec4(position, 1.0); }

	Attr getAttribute() const { return attribute; }

private:
	Math::Vector3dd position;
	Attr attribute;
};

	}
}