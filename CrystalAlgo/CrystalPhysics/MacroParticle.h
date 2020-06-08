#pragma once

#include "MicroParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Algo {
		namespace Physics {

			class MacroParticle
			{
			public:
				explicit MacroParticle(const double radius) :
					radius(radius)
				{}

				void distributePoints(const int unum, const int vnum);

				double calculateDensity();

				void calculatePressure();

				void calculateViscosity();

				//	void stepTime(double dt);

				double getRadius() const { return radius; }

				std::vector<MicroParticle*> getPoints() { return points; }

				void setInnerPoints(const std::list<Shape::IPoint*>& inners) { this->innerPoints; }

				Math::Vector3dd getPosition() const { return position; }

				Math::Vector3dd getVelocity() const { return velocity; }

			private:
				double radius;
				std::vector<MicroParticle*> points;
				std::list<Shape::IPoint*> innerPoints;
				Math::Vector3dd force;
				Math::Vector3dd position;
				Math::Vector3dd velocity;
			};

		}
	}
}