#pragma once

#include "KFMicroParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class KFFluidScene;

class KFBoundaryParticle : public Shape::IParticle
{
public:
	KFBoundaryParticle(const double radius, const Math::Vector3dd& position);

	~KFBoundaryParticle();

	void setScene(KFFluidScene* scene) { this->scene = scene; }

	KFFluidScene* getScene() { return scene; }

	//void addMicro(KFMicroParticle* microParticle);

	float getRadius() const { return radius; }

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	//void addBoundaryCount(const int count) { this->boundaryCount += count; }

	//float getDensity() const;

	//void addMicroCount(int count) { this->microCount+=count; }

private:
	float radius;
	Math::Vector3df position;
	KFFluidScene* scene;
};

	}
}