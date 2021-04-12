#pragma once

#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Shape/Volume.h"

namespace Crystal {
	namespace Physics {

class FLIPSParticle : public Shape::IParticle
{
public:
	explicit FLIPSParticle(const Math::Vector3df& position) :
		position(position)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	void translate(const Math::Vector3df& v) { this->position += v; }

private:
	Math::Vector3df position;
};

class FLIPSGridCell
{
public:
	void calculateDensity();

	void calculatePressure();

	std::vector<FLIPSParticle*> particles;

	float getDensity() const { return density; }

	float getPressure() const { return pressure; }

private:
	float density;
	float pressure;
};

class FLIPSGrid
{
public:
	void solvePressure();

	void solveViscosity();

	//float cellLength;
	Shape::Volume<FLIPSGridCell*> cells;
	//Math::Box3d boundingBox;
};

class FLIPSSolver
{
public:
	void solve(const float dt);
private:
	std::vector<FLIPSParticle*> particles;
	FLIPSGrid grid;
	//Shape::Volume<float> grid;
};
	}
}