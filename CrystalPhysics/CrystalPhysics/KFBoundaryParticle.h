#pragma once

#include "../../Crystal/Shape/IParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class KFBoundaryScene;

class KFBoundaryParticle : public Shape::IParticle
{
public:
	KFBoundaryParticle(const float radius, const Math::Vector3dd& position) :
		radius(radius),
		position(position),
		scene(nullptr)
	{}

	~KFBoundaryParticle() {}

	void setScene(KFBoundaryScene* scene) { this->scene = scene; }

	KFBoundaryScene* getScene() { return scene; }

	void stepTime(const float dt) {}

	float getRadius() const { return radius; }

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3dd getVelocity() const { return Math::Vector3dd(0,0,0); }

	float getDensity() const { return 1.0f; }

private:
	float radius;
	Math::Vector3df position;
	KFBoundaryScene* scene;
};

	}
}